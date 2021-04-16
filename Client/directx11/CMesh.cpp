#include "StdInc.h"

CMesh::CMesh(CDirectx11* pDirectx11, std::vector<Vertex> vertices, std::vector<unsigned int> indices) : m_pDirectx11(pDirectx11), m_vecVertices(vertices), m_vecIndices(indices)
{
    CreateVertexBuffer();
    CreateIndexBuffer();
}

void CMesh::CreateVertexBuffer()
{
    BufferDesc VertBuffDesc;
    VertBuffDesc.Name = "Cube vertex buffer";
    VertBuffDesc.Usage = USAGE_IMMUTABLE;
    VertBuffDesc.BindFlags = BIND_VERTEX_BUFFER;
    VertBuffDesc.uiSizeInBytes = m_vecVertices.size() * sizeof(Vertex);
    BufferData VBData;
    VBData.pData = &m_vecVertices[0];
    VBData.DataSize = m_vecVertices.size() * sizeof(Vertex);
    m_pDirectx11->GetDevice()->CreateBuffer(VertBuffDesc, &VBData, &m_vertexBuffer);
}


void CMesh::CreateIndexBuffer()
{
    BufferDesc IndBuffDesc;
    IndBuffDesc.Name = "Cube index buffer";
    IndBuffDesc.Usage = USAGE_IMMUTABLE;
    IndBuffDesc.BindFlags = BIND_INDEX_BUFFER;
    IndBuffDesc.uiSizeInBytes = m_vecIndices.size() * sizeof(Vertex);
    BufferData IBData;
    IBData.pData = &m_vecIndices[0];
    IBData.DataSize = m_vecIndices.size() * sizeof(Vertex);
    m_pDirectx11->GetDevice()->CreateBuffer(IndBuffDesc, &IBData, &m_indexBuffer);
}

void CMesh::Draw()
{
    Uint32   offset = 0;
    IBuffer* pBuffs[] = {m_vertexBuffer};
    m_pDirectx11->GetImmediateContext()->SetVertexBuffers(0, 1, pBuffs, &offset, RESOURCE_STATE_TRANSITION_MODE_TRANSITION, SET_VERTEX_BUFFERS_FLAG_RESET);
    m_pDirectx11->GetImmediateContext()->SetIndexBuffer(m_indexBuffer, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_pDirectx11->SetDefaultPipeline();
    DrawIndexedAttribs DrawAttrs;               // This is an indexed draw call
    DrawAttrs.IndexType = VT_UINT32;            // Index type
    DrawAttrs.NumIndices = m_vecIndices.size();
    // Verify the state of vertex and index buffers as well as consistence of
    // render targets and correctness of draw command arguments
    DrawAttrs.Flags = DRAW_FLAG_VERIFY_ALL;
    m_pDirectx11->GetImmediateContext()->DrawIndexed(DrawAttrs);
}

CMesh::~CMesh()
{
    m_vertexBuffer->Release();
    m_indexBuffer->Release();
}
