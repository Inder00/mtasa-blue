#include "StdInc.h"
#include <cassert>
#include <thread>

CDirectx11::CDirectx11(CCoreBasicInterface* pBasicInterface) : m_pBasicInterface(pBasicInterface)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void CDirectx11::DoPulse()
{
    if (!m_pFactoryD3D11 && m_pBasicInterface->GetHookedWindow() != 0)
    {
        printf("Hook %i\n", m_pBasicInterface->GetHookedWindow());
        Create(m_pBasicInterface->GetHookedWindow());
    }

    const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
    auto*       pRTV = m_swapChain->GetCurrentBackBufferRTV();
    auto*       pDSV = m_swapChain->GetDepthBufferDSV();
    m_contexts->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_contexts->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    m_swapChain->Present();
}
void CDirectx11::Create(HWND window)
{
    m_pFactoryD3D11 = GetEngineFactoryD3D11();
    EngineD3D11CreateInfo EngineCI;
    SwapChainDesc         chainDesc;

    m_pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_device, &m_contexts);
    m_pFactoryD3D11->CreateSwapChainD3D11(m_device, m_contexts, chainDesc, FullScreenModeDesc{}, NativeWindow{window},
                                          &m_swapChain);

    //TextureDesc TexDesc;
    //TexDesc.Name = "MEA";
    //TexDesc.Type = RESOURCE_DIM_TEX_2D;
    //TexDesc.Width = 1024;
    //TexDesc.Height = 1024;
    //TexDesc.Format = TEX_FORMAT_RGBA8_UNORM;
    //TexDesc.Usage = USAGE_DEFAULT;
    //TexDesc.BindFlags = BIND_SHADER_RESOURCE | BIND_RENDER_TARGET | BIND_UNORDERED_ACCESS;
    //ITexture* m_pTestTex;
    //m_device->CreateTexture(TexDesc, nullptr, &m_pTestTex);

    //RenderPassDesc RPDesc;
    //RPDesc.Name = "PSOCreationFailureTest - render pass";
    //RenderPassAttachmentDesc Attachments[2]{};
    //Attachments[0].Format = TEX_FORMAT_RGBA8_UNORM;
    //Attachments[0].InitialState = RESOURCE_STATE_RENDER_TARGET;
    //Attachments[0].FinalState = RESOURCE_STATE_RENDER_TARGET;
    //Attachments[1].Format = TEX_FORMAT_D32_FLOAT;
    //Attachments[1].InitialState = RESOURCE_STATE_DEPTH_WRITE;
    //Attachments[1].FinalState = RESOURCE_STATE_DEPTH_WRITE;
    //RPDesc.AttachmentCount = _countof(Attachments);
    //RPDesc.pAttachments = Attachments;

    //AttachmentReference ColorAttachmentRef{0, RESOURCE_STATE_RENDER_TARGET};
    //AttachmentReference DepthAttachmentRef{1, RESOURCE_STATE_DEPTH_WRITE};
    //SubpassDesc         Subpasses[1]{};
    //Subpasses[0].RenderTargetAttachmentCount = 1;
    //Subpasses[0].pRenderTargetAttachments = &ColorAttachmentRef;
    //Subpasses[0].pDepthStencilAttachment = &DepthAttachmentRef;

    //RPDesc.SubpassCount = _countof(Subpasses);
    //RPDesc.pSubpasses = Subpasses;
    //IRenderPass* m_pRenderPass;

    //m_device->CreateRenderPass(RPDesc, &m_pRenderPass);
}
