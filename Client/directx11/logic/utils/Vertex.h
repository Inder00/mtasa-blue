#include <array>

struct Vertex
{
    float3 position;
    float  padding;

    static std::array<LayoutElement, 1> GetLayout() { return {LayoutElement{0, 0, 3, VT_FLOAT32, false}}; }
};

struct ColorVertex : public Vertex
{
    ColorVertex(float3 position, float4 color) : color(color) { this->position = position; }
    float4 color;

    static std::array<LayoutElement, 2> GetLayout() { return {Vertex::GetLayout()[0], LayoutElement{1, 0, 4, VT_FLOAT32, false}}; }
};

static_assert(sizeof(ColorVertex) % sizeof(float4) == 0);
