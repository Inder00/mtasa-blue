#include "CMeshBase.h"
#include "CModelBase.h"
#include "CObjectBase.h"

struct ColorVertex;
struct CMesh;

class CDirectx11Base
{
public:
    virtual void         DoPulse() = 0;
    virtual CMeshBase*   CreateMesh(const std::vector<ColorVertex>& vertices, const std::vector<Uint32>& indices) = 0;
    virtual CModelBase*  CreateModel(unsigned int id, CMeshBase* pMesh) = 0;
    virtual CObjectBase* CreateObject(unsigned int id, Diligent::float3 position) = 0;
};
