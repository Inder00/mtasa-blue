class CModel;

class CObject : public CObjectBase
{
    friend class CModel;

public:
    CObject(CModel* pModel, float3 position);
    void Render();
    void SetPosition(float3 position);
    void SetRotation(float3 posrotationition);

private:
    CModel*  m_pModel;
    float4x4 m_matrix;
};
