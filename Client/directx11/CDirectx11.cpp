#include "StdInc.h"
#include <cassert>

CDirectx11::CDirectx11(HWND nativeWindowHandle) : m_nativeWindowHandle(nativeWindowHandle)
{
    assert(!nativeWindowHandle);
    m_pFactoryD3D11 = GetEngineFactoryD3D11();
    EngineD3D11CreateInfo EngineCI;
    SwapChainDesc         chainDesc;

    m_pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_device, &m_contexts);
    m_pFactoryD3D11->CreateSwapChainD3D11(m_device, m_contexts, chainDesc, FullScreenModeDesc{}, NativeWindow{m_nativeWindowHandle}, &m_swapChain);
}
