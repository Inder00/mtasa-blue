/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        CPrimitiveBatcher.h
 *  PURPOSE:
 *
 *
 *****************************************************************************/
// Vertex type used by the primitives batcher
struct sPrimitive
{
    D3DPRIMITIVETYPE               eType;
    std::vector<PrimitiveVertice>* pVecVertices;
};

//
// Batches primitives drawing
//
class CPrimitiveBatcher : public C2DBatcher
{
public:
    ZERO_ON_NEW
    CPrimitiveBatcher(CGraphics* graphics) : C2DBatcher(graphics){};
    void SetDeviceStates();
    void Flush();
    void DrawPrimitive(D3DPRIMITIVETYPE eType, size_t iSize, const void* pDataAddr, size_t iVertexStride);
    void ClearQueue();
    void AddPrimitive(D3DPRIMITIVETYPE eType, std::vector<PrimitiveVertice>* pVecVertices);

protected:
    std::vector<sPrimitive> m_primitiveList;
};
