class CMeshBase;

class CMesh : public CMeshBase
{
public:
    CMesh(CDirectx11* pDirectx11, std::vector<ColorVertex> vertices, std::vector<Uint32> indices);
    void Draw();
    void CreateVertexBuffer();
    void CreateIndexBuffer();

    ~CMesh();

    CDirectx11* GetDirectx11() const { return m_pDirectx11; }

private:
    CDirectx11*         m_pDirectx11;
    std::vector<ColorVertex> m_vecVertices;
    std::vector<Uint32> m_vecIndices;

    IBuffer* m_vertexBuffer = nullptr;
    IBuffer* m_indexBuffer = nullptr;
};
