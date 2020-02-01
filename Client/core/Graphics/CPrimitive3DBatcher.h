/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CPrimitive3DBatcher.h
 *  PURPOSE:
 *
 *  Multi Theft Auto is available from http://www.multitheftauto.com/
 *
 *****************************************************************************/

#pragma once

// Vertex type used by the primitives 3d batcher
struct sPrimitive3D
{
    D3DPRIMITIVETYPE                 eType;
    std::vector<PrimitiveVertice>*   pVecVertices;
};

//
// Batches primitives drawing
//
class CPrimitive3DBatcher : public C3DBatcher
{
public:
    CPrimitive3DBatcher(bool bPreGUI, CGraphics* pGraphics) : C3DBatcher(pGraphics), m_bPreGUI(bPreGUI) {}
    void Flush();
    void AddPrimitive(D3DPRIMITIVETYPE eType, std::vector<PrimitiveVertice>* pVecVertices);
    void DrawPrimitive(D3DPRIMITIVETYPE eType, size_t iCollectionSize, const void* pDataAddr, size_t uiVertexStride);
    bool HasItems() const { return !m_primitiveList.empty(); }

protected:
    bool m_bPreGUI;
    std::vector<sPrimitive3D> m_primitiveList;
};
