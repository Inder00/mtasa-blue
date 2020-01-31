/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CPrimitiveMaterialBatcher.h
 *  PURPOSE:
 *
 *
 *****************************************************************************/
// Vertex type used by the primitives batcher
struct sPrimitiveMaterial
{
    D3DPRIMITIVETYPE                        eType;
    CMaterialItem*                          pMaterial;
    std::vector<PrimitiveMaterialVertice>*  pVecVertices;
};
//
// Batches primitives drawing
//
class CPrimitiveMaterialBatcher : public C2DBatcher
{
    friend CGraphics;

public:
    ZERO_ON_NEW
    CPrimitiveMaterialBatcher(CGraphics* graphics) : C2DBatcher(graphics){};
    void SetDeviceStates();
    void Flush();
    void DrawPrimitive(D3DPRIMITIVETYPE eType, size_t iSize, const void* pDataAddr, size_t iVertexStride);
    void ClearQueue();
    void AddPrimitive(D3DPRIMITIVETYPE eType, CMaterialItem* pMaterial, std::vector<PrimitiveMaterialVertice>* pVecVertices);

protected:
    std::vector<sPrimitiveMaterial> m_primitiveList;
};
