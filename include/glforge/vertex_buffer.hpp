#ifndef GL_FORGE_VERTEX_BUFFER_HPP
#define GL_FORGE_VERTEX_BUFFER_HPP

#include <glad/glad.h>
#include <span>

namespace glforge
{

class VertexBuffer
{
public:
    VertexBuffer(std::span<const float> buffer_data, GLuint stride);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer(VertexBuffer&& rhs) noexcept;
    VertexBuffer& operator=(const VertexBuffer&) = delete;
    VertexBuffer& operator=(VertexBuffer&& rhs) noexcept;
    ~VertexBuffer();

    [[nodiscard]] GLuint id() const noexcept;
    [[nodiscard]] GLuint stride() const noexcept;

    /*
    Update the vertex buffer contents. This member function does not
    allocate more memory.
    */
    void update(std::span<const float> buffer_data);

private:
    GLuint _id{0};
    GLuint _stride{0};
};

} // namespace glforge

#endif // GL_FORGE_VERTEX_BUFFER_HPP