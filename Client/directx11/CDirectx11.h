class CDirectx11Base;
class CCoreBasicInterface;

class CDirectx11 : public CDirectx11Base
{
public:
    CDirectx11(CCoreBasicInterface* nativeWindowHandle);
    void            CreatePipelineState();
    void DoPulse();
    void            CreateMesh(const std::vector<Vertex>& vertices, const std::vector<Uint32> indices);
    IRenderDevice*  GetDevice() const { return m_pDevice; }
    IDeviceContext* GetImmediateContext() const { return m_pImmediateContext; }
    void            SetDefaultPipeline();

        private:
    std::vector<std::unique_ptr<CMesh>> m_vecMeshes;
    void                 Create(HWND window);

    CCoreBasicInterface* m_pBasicInterface;

    IEngineFactoryD3D11* m_pFactoryD3D11 = nullptr;
    IRenderDevice*       m_pDevice;
    IDeviceContext*      m_pImmediateContext;
    ISwapChain*          m_pSwapChain;

    
    RefCntAutoPtr<IPipelineState>         m_pPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
    RefCntAutoPtr<IBuffer>                m_VSConstants;
};
