#include "StdInc.h"

CModel::CModel(CMesh* pMesh) : m_pMesh(pMesh)
{
    CreatePipeline();
}

struct VSConstants
{
    float4x4 WorldViewProj;
    //float4x4 View;
    //float4x4 Projection;
};

void CModel::CreatePipeline()
{
    CDirectx11* pDirectx = m_pMesh->GetDirectx11();
    // Pipeline state object encompasses configuration of all GPU stages

    GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Cube PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    PSOCreateInfo.GraphicsPipeline.NumRenderTargets             = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0]                = pDirectx->GetSwapChain()->GetDesc().ColorBufferFormat;
    // Set depth buffer format which is the format of the swap chain's back buffer
    PSOCreateInfo.GraphicsPipeline.DSVFormat                    = pDirectx->GetSwapChain()->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSOCreateInfo.GraphicsPipeline.PrimitiveTopology            = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // Cull back faces
    PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode      = CULL_MODE_BACK;
    // Enable depth testing
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;
    // clang-format on

    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood.
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.UseCombinedTextureSamplers = true;

    // In this tutorial, we will load shaders from file. To be able to do that,
    // we need to create a shader source stream factory
    RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
    pDirectx->GetEngineFactory()->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;
    // Create a vertex shader
    RefCntAutoPtr<IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube VS";
        ShaderCI.FilePath = "D:\\VISUAL STUDIO\\mtasa-blue\\bintests\\Directx11\\cube.vsh";
        pDirectx->GetDevice()->CreateShader(ShaderCI, &pVS);
        // Create dynamic uniform buffer that will store our transformation matrix
        // Dynamic buffers can be frequently updated by the CPU
        BufferDesc CBDesc;
        CBDesc.Name = "VS constants CB";
        CBDesc.uiSizeInBytes = sizeof(VSConstants);
        CBDesc.Usage = USAGE_DYNAMIC;
        CBDesc.BindFlags = BIND_UNIFORM_BUFFER;
        CBDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
        pDirectx->GetDevice()->CreateBuffer(CBDesc, nullptr, &m_VSConstants);
    }

    // Create a pixel shader
    RefCntAutoPtr<IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube PS";
        ShaderCI.FilePath = "D:\\VISUAL STUDIO\\mtasa-blue\\bintests\\Directx11\\cube.psh";
        pDirectx->GetDevice()->CreateShader(ShaderCI, &pPS);
    }

    PSOCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = ColorVertex::GetLayout().data();
    PSOCreateInfo.GraphicsPipeline.InputLayout.NumElements = ColorVertex::GetLayout().size();

    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;

    // Define variable type that will be used by default
    PSOCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

    pDirectx->GetDevice()->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);
    if (!m_pPSO)
    {
        printf("Error while creating a shader\n");
        return;
    }

    // Since we did not explcitly specify the type for 'Constants' variable, default
    // type (SHADER_RESOURCE_VARIABLE_TYPE_STATIC) will be used. Static variables never
    // change and are bound directly through the pipeline state object.
    auto* constaints = m_pPSO->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants");
    if (constaints)
    {
        m_pPSO->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(m_VSConstants);
    }
    else
    {
        printf("'Constants' not found!\n");
        return;
    }

    // Create a shader resource binding object and bind all static resources in it
    m_pPSO->CreateShaderResourceBinding(&m_pSRB, true);
}

float4x4 GetAdjustedProjectionMatrix(CDirectx11* pDirectx11, float FOV, float NearPlane, float FarPlane)
{
    const auto& SCDesc = pDirectx11->GetSwapChain()->GetDesc();

    float AspectRatio = static_cast<float>(SCDesc.Width) / static_cast<float>(SCDesc.Height);
    float XScale, YScale;
    if (SCDesc.PreTransform == SURFACE_TRANSFORM_ROTATE_90 || SCDesc.PreTransform == SURFACE_TRANSFORM_ROTATE_270 ||
        SCDesc.PreTransform == SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90 || SCDesc.PreTransform == SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270)
    {
        // When the screen is rotated, vertical FOV becomes horizontal FOV
        XScale = 1.f / std::tan(FOV / 2.f);
        // Aspect ratio is inversed
        YScale = XScale * AspectRatio;
    }
    else
    {
        YScale = 1.f / std::tan(FOV / 2.f);
        XScale = YScale / AspectRatio;
    }

    float4x4 Proj;
    Proj._11 = XScale;
    Proj._22 = YScale;
    Proj.SetNearFarClipPlanes(NearPlane, FarPlane, pDirectx11->GetDevice()->GetDeviceCaps().IsGLDevice());
    return Proj;
}

float4x4 GetSurfacePretransformMatrix(CDirectx11* pDirectx11, const float3& f3CameraViewAxis)
{
    const auto& SCDesc = pDirectx11->GetSwapChain()->GetDesc();
    switch (SCDesc.PreTransform)
    {
        case SURFACE_TRANSFORM_ROTATE_90:
            // The image content is rotated 90 degrees clockwise.
            return float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F / 2.f);

        case SURFACE_TRANSFORM_ROTATE_180:
            // The image content is rotated 180 degrees clockwise.
            return float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F);

        case SURFACE_TRANSFORM_ROTATE_270:
            // The image content is rotated 270 degrees clockwise.
            return float4x4::RotationArbitrary(f3CameraViewAxis, -PI_F * 3.f / 2.f);

        case SURFACE_TRANSFORM_OPTIMAL:
            UNEXPECTED("SURFACE_TRANSFORM_OPTIMAL is only valid as parameter during swap chain initialization.");
            return float4x4::Identity();

        case SURFACE_TRANSFORM_HORIZONTAL_MIRROR:
        case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90:
        case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180:
        case SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270:
            UNEXPECTED("Mirror transforms are not supported");
            return float4x4::Identity();

        default:
            return float4x4::Identity();
    }
}

void CModel::Draw(float4x4 matrix)
{
    IDeviceContext* pImmediateContext = m_pMesh->GetDirectx11()->GetImmediateContext();
    pImmediateContext->SetPipelineState(m_pPSO);
    pImmediateContext->CommitShaderResources(m_pSRB, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    VSConstants values;

    // Camera is at (0, 0, -5) looking along the Z axis
    float4x4 View = float4x4::Translation(0.f, 0.0f, -200.0f);

    // Get pretransform matrix that rotates the scene according the surface orientation
    auto SrfPreTransform = GetSurfacePretransformMatrix(m_pMesh->GetDirectx11() , float3{0, 0, 1});

    // Get projection matrix adjusted to the current screen orientation
    auto Proj = GetAdjustedProjectionMatrix(m_pMesh->GetDirectx11(), PI_F / 4.0f, 0.01f, 100.f);

    // Compute world-view-projection matrix
    values.WorldViewProj = matrix * View * SrfPreTransform * Proj;
    SetShaderValues(values);

    m_pMesh->Draw();
}
