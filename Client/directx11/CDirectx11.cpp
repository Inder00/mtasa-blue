#include "StdInc.h"
#include <cassert>
#include <thread>

CDirectx11::CDirectx11(CCoreBasicInterface* pBasicInterface) : m_pBasicInterface(pBasicInterface)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    std::thread test = std::thread([&]() {
        Sleep(1000);
        Create(m_pBasicInterface->GetHookedWindow());
    });
    test.detach();
}

void CDirectx11::Create(HWND window)
{
    m_pFactoryD3D11 = GetEngineFactoryD3D11();
    EngineD3D11CreateInfo EngineCI;
    SwapChainDesc         chainDesc;

    m_pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_device, &m_contexts);
    m_pFactoryD3D11->CreateSwapChainD3D11(m_device, m_contexts, chainDesc, FullScreenModeDesc{}, NativeWindow{window},
                                          &m_swapChain);
}
