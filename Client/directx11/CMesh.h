class CMesh
{
public:
    CMesh(CDirectx11* pDirectx11, std::vector<Vertex> vertices, std::vector<Uint32> indices);
    void Draw();
    void CreateVertexBuffer();
    void CreateIndexBuffer();

    ~CMesh();

private:
    CDirectx11*         m_pDirectx11;
    std::vector<Vertex> m_vecVertices;
    std::vector<Uint32> m_vecIndices;

    IBuffer* m_vertexBuffer = nullptr;
    IBuffer* m_indexBuffer = nullptr;
};
