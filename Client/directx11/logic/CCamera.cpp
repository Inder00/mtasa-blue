#include "StdInc.h"

void CCamera::Update()
{
    float4x4 ReferenceRotation = GetReferenceRotiation();

    float4x4 CameraRotation =
        float4x4::RotationArbitrary(m_ReferenceUpAxis, m_fYawAngle) * float4x4::RotationArbitrary(m_ReferenceRightAxis, m_fPitchAngle) * ReferenceRotation;
    float4x4 WorldRotation = CameraRotation.Transpose();

    m_ViewMatrix = float4x4::Translation(-m_Pos) * CameraRotation;
    m_WorldMatrix = WorldRotation * float4x4::Translation(m_Pos);
}

float4x4 CCamera::GetReferenceRotiation() const
{
    // clang-format off
    return float4x4
    {
        m_ReferenceRightAxis.x, m_ReferenceUpAxis.x, m_ReferenceAheadAxis.x, 0,
        m_ReferenceRightAxis.y, m_ReferenceUpAxis.y, m_ReferenceAheadAxis.y, 0,
        m_ReferenceRightAxis.z, m_ReferenceUpAxis.z, m_ReferenceAheadAxis.z, 0,
                             0,                   0,                      0, 1
    };
    // clang-format on
}

void CCamera::SetReferenceAxes(const float3& ReferenceRightAxis, const float3& ReferenceUpAxis, bool IsRightHanded)
{
    m_ReferenceRightAxis = normalize(ReferenceRightAxis);
    m_ReferenceUpAxis = ReferenceUpAxis - dot(ReferenceUpAxis, m_ReferenceRightAxis) * m_ReferenceRightAxis;
    auto            UpLen = length(m_ReferenceUpAxis);
    constexpr float Epsilon = 1e-5f;
    if (UpLen < Epsilon)
    {
        UpLen = Epsilon;
        LOG_WARNING_MESSAGE("Right and Up axes are collinear");
    }
    m_ReferenceUpAxis /= UpLen;

    m_fHandness = IsRightHanded ? +1.f : -1.f;
    m_ReferenceAheadAxis = m_fHandness * cross(m_ReferenceRightAxis, m_ReferenceUpAxis);
    auto AheadLen = length(m_ReferenceAheadAxis);
    if (AheadLen < Epsilon)
    {
        AheadLen = Epsilon;
        LOG_WARNING_MESSAGE("Ahead axis is not well defined");
    }
    m_ReferenceAheadAxis /= AheadLen;
}

void CCamera::SetLookAt(const float3& LookAt)
{
    float3 ViewDir = LookAt - m_Pos;

    ViewDir = ViewDir * GetReferenceRotiation();

    m_fYawAngle = atan2f(ViewDir.x, ViewDir.z);

    float fXZLen = sqrtf(ViewDir.z * ViewDir.z + ViewDir.x * ViewDir.x);
    m_fPitchAngle = -atan2f(ViewDir.y, fXZLen);
}

void CCamera::SetRotation(float Yaw, float Pitch)
{
    m_fYawAngle = Yaw;
    m_fPitchAngle = Pitch;
}

void CCamera::SetProjAttribs(Float32 NearClipPlane, Float32 FarClipPlane, Float32 AspectRatio, Float32 FOV, SURFACE_TRANSFORM SrfPreTransform,
                                       bool IsGL)
{
    m_ProjAttribs.NearClipPlane = NearClipPlane;
    m_ProjAttribs.FarClipPlane = FarClipPlane;
    m_ProjAttribs.AspectRatio = AspectRatio;
    m_ProjAttribs.FOV = FOV;
    m_ProjAttribs.PreTransform = SrfPreTransform;
    m_ProjAttribs.IsGL = IsGL;

    float XScale, YScale;
    if (SrfPreTransform == SURFACE_TRANSFORM_ROTATE_90 || SrfPreTransform == SURFACE_TRANSFORM_ROTATE_270 ||
        SrfPreTransform == SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90 || SrfPreTransform == SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270)
    {
        // When the screen is rotated, vertical FOV becomes horizontal FOV
        XScale = 1.f / std::tan(FOV / 2.f);
        // Aspect ratio is width/height accounting for pretransform
        YScale = XScale / AspectRatio;
    }
    else
    {
        YScale = 1.f / std::tan(FOV / 2.f);
        XScale = YScale / AspectRatio;
    }

    float4x4 Proj;
    Proj._11 = XScale;
    Proj._22 = YScale;
    Proj.SetNearFarClipPlanes(NearClipPlane, FarClipPlane, IsGL);

    m_ProjMatrix = float4x4::Projection(m_ProjAttribs.FOV, m_ProjAttribs.AspectRatio, m_ProjAttribs.NearClipPlane, m_ProjAttribs.FarClipPlane, IsGL);
}

