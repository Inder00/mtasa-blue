class CDirectx11Base;

class CDirectx11 : public CDirectx11Base
{
public:
    CDirectx11(HWND nativeWindowHandle);

private:
    HWND m_nativeWindowHandle;

    IEngineFactoryD3D11* m_pFactoryD3D11;
    IRenderDevice*  m_device;
    IDeviceContext* m_contexts;
    ISwapChain*     m_swapChain;
};
