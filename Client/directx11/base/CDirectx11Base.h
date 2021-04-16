struct Vertex;

class CDirectx11Base
{
public:
    virtual void DoPulse() = 0;
    virtual void CreateMesh(const std::vector<Vertex>& vertices, const std::vector<Uint32> indices) = 0;
};
