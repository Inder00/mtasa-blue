#include "StdInc.h"
#include <diligentCore/Common/interface/BasicMath.hpp>

CDirectx11::CDirectx11(CCoreBasicInterface* pBasicInterface) : m_pBasicInterface(pBasicInterface)
{
    m_pCamera = std::make_unique<CCamera>();
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void CDirectx11::CreatePipelineState()
{

}

void CDirectx11::DoPulse()
{
    printf("------- RENDER START -------\n");
    if (!m_pFactoryD3D11 && m_pBasicInterface->GetHookedWindow() != 0)
    {
        printf("Hook %p\n", m_pBasicInterface->GetHookedWindow());
        Create(m_pBasicInterface->GetHookedWindow());
    }

    m_pCamera->Update();
    const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
    auto*       pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    auto*       pDSV = m_pSwapChain->GetDepthBufferDSV();

    m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
   
    m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    for (const auto& pObject : m_vecObjects)
    {
        pObject->Render();
    };
    m_pSwapChain->Present();
    printf("------- RENDER END -------\n");
}

CMeshBase* CDirectx11::CreateMesh(const std::vector<ColorVertex>& vertices, const std::vector<Uint32>& indices)
{
    return InternalCreateMesh(vertices, indices);
}

CMesh* CDirectx11::InternalCreateMesh(const std::vector<ColorVertex>& vertices, const std::vector<Uint32> indices)
{
    m_vecMeshes.push_back(std::make_unique<CMesh>(this, vertices, indices));
    return m_vecMeshes.back().get();
}

CModelBase* CDirectx11::CreateModel(unsigned int id, CMeshBase* pMesh)
{
    return InternalCreateModel(id, (CMesh*)pMesh);
}

CObjectBase* CDirectx11::CreateObject(unsigned int id, float3 position)
{
    return InternalCreateObject(id, position);
}

CModel* CDirectx11::InternalCreateModel(unsigned int id, CMesh* pMesh)
{
    assert(m_mapModels.find(id) == m_mapModels.end());
    m_mapModels[id] = std::make_unique<CModel>(pMesh);
    return m_mapModels[id].get();
}

CObject* CDirectx11::InternalCreateObject(unsigned int id, float3 position)
{
    assert(m_mapModels.find(id) != m_mapModels.end());
    m_vecObjects.push_back(std::make_unique<CObject>(m_mapModels[id].get(), position));
    return m_vecObjects.back().get();
}


void CDirectx11::Create(HWND window)
{
    m_pFactoryD3D11 = GetEngineFactoryD3D11();
    EngineD3D11CreateInfo EngineCI;
    SwapChainDesc         chainDesc;

    m_pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
    m_pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, chainDesc, FullScreenModeDesc{}, NativeWindow{window}, &m_pSwapChain);

    CreatePipelineState();
}
