class CDirectx11;

#include "CObject.h"
#include "CModel.h"
#include "CMesh.h"

class CCoreBasicInterface;

class CDirectx11 : public CDirectx11Base
{
public:
    CDirectx11(CCoreBasicInterface* nativeWindowHandle);
    void         CreatePipelineState();
    void         DoPulse();
    CMeshBase*   CreateMesh(const std::vector<ColorVertex>& vertices, const std::vector<Uint32>& indices);
    CModelBase*  CreateModel(unsigned int id, CMeshBase* pMesh);
    CObjectBase* CreateObject(unsigned int id, float3 position);

    IRenderDevice*  GetDevice() const { return m_pDevice; }
    IDeviceContext* GetImmediateContext() const { return m_pImmediateContext; }
    ISwapChain*     GetSwapChain() const { return m_pSwapChain; }
    IEngineFactoryD3D11* GetEngineFactory() const { return m_pFactoryD3D11; }
    CCamera* GetCamera() const { return m_pCamera.get(); }

private:
    CMesh*   InternalCreateMesh(const std::vector<ColorVertex>& vertices, const std::vector<Uint32> indices);
    CModel*  InternalCreateModel(unsigned int id, CMesh* pMesh);
    CObject* InternalCreateObject(unsigned int id, float3 position);

    std::vector<std::unique_ptr<CMesh>>             m_vecMeshes;
    std::map<unsigned int, std::unique_ptr<CModel>> m_mapModels;
    std::vector<std::unique_ptr<CObject>>           m_vecObjects;

    void Create(HWND window);

    CCoreBasicInterface* m_pBasicInterface;

    IEngineFactoryD3D11* m_pFactoryD3D11 = nullptr;
    IRenderDevice*       m_pDevice = nullptr;
    IDeviceContext*      m_pImmediateContext = nullptr;
    ISwapChain*          m_pSwapChain = nullptr;

    std::unique_ptr<CCamera> m_pCamera;
};
