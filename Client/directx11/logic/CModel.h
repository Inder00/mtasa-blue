class CMesh;

class CModel : public CModelBase
{
public:
    CModel(CMesh* pMesh);

    void Draw(float4x4 matrix);

    void CreatePipeline();

private:
    CMesh* m_pMesh;

    RefCntAutoPtr<IPipelineState>         m_pPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
    RefCntAutoPtr<IBuffer>                m_VSConstants;
};
