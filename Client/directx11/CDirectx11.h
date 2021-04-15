class CDirectx11Base;
class CCoreBasicInterface;

class CDirectx11 : public CDirectx11Base
{
public:
    CDirectx11(CCoreBasicInterface* nativeWindowHandle);
    void DoPulse();
private:
    void                 Create(HWND window);

    CCoreBasicInterface* m_pBasicInterface;

    IEngineFactoryD3D11* m_pFactoryD3D11 = nullptr;
    IRenderDevice*  m_device;
    IDeviceContext* m_contexts;
    ISwapChain*     m_swapChain;
};
