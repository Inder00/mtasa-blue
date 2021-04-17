class CMesh;

class CModel : public CModelBase
{
public:
    CModel(CMesh* pMesh);

    void Draw(float4x4 matrix);

    void CreatePipeline();

    template<typename T>
    void SetShaderValues(T values)
    {
        MapHelper<T> CBConstants(m_pMesh->GetDirectx11()->GetImmediateContext(), m_VSConstants, MAP_WRITE, MAP_FLAG_DISCARD);
        *CBConstants = values;
    }


private:
    CMesh* m_pMesh;

    RefCntAutoPtr<IPipelineState>         m_pPSO;
    RefCntAutoPtr<IShaderResourceBinding> m_pSRB;
    RefCntAutoPtr<IBuffer>                m_VSConstants;
};
