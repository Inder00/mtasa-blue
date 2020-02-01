/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CPrimitiveBatcher.cpp
 *  PURPOSE:
 *
 *
 *****************************************************************************/
#include <StdInc.h>
#include "C2DBatcher.h"
#include "CPrimitiveBatcher.h"

void CPrimitiveBatcher::SetDeviceStates()
{
    // Set states
    m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
    m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
    m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

void CPrimitiveBatcher::Flush()
{
    if (m_primitiveList.empty())
        return;

    // Save render states
    IDirect3DStateBlock9* pSavedStateBlock = nullptr;
    m_pDevice->CreateStateBlock(D3DSBT_ALL, &pSavedStateBlock);

    // Set transformations
    m_pDevice->SetTransform(D3DTS_WORLD, &m_MatWorld);
    m_pDevice->SetTransform(D3DTS_VIEW, &m_MatView);
    m_pDevice->SetTransform(D3DTS_PROJECTION, &m_MatProjection);

    // Set vertex FVF
    m_pDevice->SetFVF(PrimitiveVertice::FNV);

    // Set device states
    SetDeviceStates();

    // Draw
    m_pDevice->SetTexture(0, nullptr);
    for (auto& primitive : m_primitiveList)
    {
        const void* pVertexStreamZeroData = &primitive.pVecVertices->at(0);
        uint        uiVertexStreamZeroStride = sizeof(PrimitiveVertice);

        DrawPrimitive(primitive.eType, primitive.pVecVertices->size(), pVertexStreamZeroData, uiVertexStreamZeroStride);
    }

    // Clean up
    ClearQueue();
    // Restore render states
    if (pSavedStateBlock)
    {
        pSavedStateBlock->Apply();
        SAFE_RELEASE(pSavedStateBlock);
    }
}

void CPrimitiveBatcher::DrawPrimitive(D3DPRIMITIVETYPE eType, size_t iCollectionSize, const void* pDataAddr, size_t uiVertexStride)
{
    int iSize = 1;
    switch (eType)
    {
    case D3DPT_POINTLIST:
        iSize = iCollectionSize;
        break;
    case D3DPT_LINELIST:
        iSize = iCollectionSize / 2;
        break;
    case D3DPT_LINESTRIP:
        iSize = iCollectionSize - 1;
        break;
    case D3DPT_TRIANGLEFAN:
    case D3DPT_TRIANGLESTRIP:
        iSize = iCollectionSize - 2;
        break;
    case D3DPT_TRIANGLELIST:
        iSize = iCollectionSize / 3;
        break;
    }
    m_pDevice->DrawPrimitiveUP(eType, iSize, pDataAddr, uiVertexStride);
}

void CPrimitiveBatcher::ClearQueue()
{
    // Clean up
    for(auto& primitive : m_primitiveList){
        delete primitive.pVecVertices;
    }
    size_t prevSize = m_primitiveList.size();
    m_primitiveList.clear();
    m_primitiveList.reserve(prevSize);
}

void CPrimitiveBatcher::AddPrimitive(D3DPRIMITIVETYPE eType, std::vector<PrimitiveVertice>* pVecVertices)
{
    m_primitiveList.push_back({eType, pVecVertices});
}
