/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *               (Shared logic for modifications)
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CPrimitiveMaterialBatcher.cpp
 *  PURPOSE:
 *
 *
 *****************************************************************************/
#include <StdInc.h>
#include "C2DBatcher.h"
#include "CPrimitiveMaterialBatcher.h"

void CPrimitiveMaterialBatcher::SetDeviceStates()
{
    // Set states
    m_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    m_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
}

void CPrimitiveMaterialBatcher::Flush()
{
    if (m_primitiveList.empty())
        return;

    // Save render states
    IDirect3DStateBlock9* pSavedStateBlock = nullptr;
    m_pDevice->CreateStateBlock(D3DSBT_ALL, &pSavedStateBlock);
    // Set transformations
    D3DXMATRIX matWorld;
    D3DXMatrixIdentity(&matWorld);
    m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
    m_pDevice->SetTransform(D3DTS_VIEW, &m_MatView);
    m_pDevice->SetTransform(D3DTS_PROJECTION, &m_MatProjection);

    // Set vertex FVF
    m_pDevice->SetFVF(PrimitiveMaterialVertice::FNV);

    // Set device states
    SetDeviceStates();

    // Draw
    m_pDevice->SetTexture(0, nullptr);

    for (auto& primitive : m_primitiveList)
    {
        const void* pVertexStreamZeroData = &primitive.pVecVertices->at(0);
        uint        uiVertexStreamZeroStride = sizeof(PrimitiveMaterialVertice);

        CMaterialItem* pMaterial = primitive.pMaterial;
        pMaterial->Use([primitive, pVertexStreamZeroData, uiVertexStreamZeroStride, this]() {
            DrawPrimitive(primitive.eType, primitive.pVecVertices->size(), pVertexStreamZeroData, uiVertexStreamZeroStride);
        });
        m_pGraphics->RemoveQueueRef(pMaterial);
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

void CPrimitiveMaterialBatcher::DrawPrimitive(D3DPRIMITIVETYPE eType, size_t iCollectionSize, const void* pDataAddr, size_t uiVertexStride)
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

void CPrimitiveMaterialBatcher::ClearQueue()
{
    // Clean up
    for (auto& primitive : m_primitiveList)
    {
        delete primitive.pVecVertices;
    }

    size_t prevSize = m_primitiveList.size();
    m_primitiveList.clear();
    m_primitiveList.reserve(prevSize);
}

void CPrimitiveMaterialBatcher::AddPrimitive(D3DPRIMITIVETYPE eType, CMaterialItem* pMaterial, std::vector<PrimitiveMaterialVertice>* pVecVertices)
{
    m_primitiveList.push_back({eType, pMaterial, pVecVertices});
}
