#include "StdInc.h"

CObject::CObject(CModel* pModel, float3 position) : m_pModel(pModel), m_matrix(float4x4::Translation(position))
{
    m_matrix.Projection(70, 16.0f / 9.0f, 0.1f, 200.0f, false);
}

void CObject::Render()
{
    m_pModel->Draw(m_matrix);
}

void CObject::SetPosition(float3 position)
{
    m_matrix.m30 = position.x;
    m_matrix.m31 = position.y;
    m_matrix.m32 = position.z;
}
