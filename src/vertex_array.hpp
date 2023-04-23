#ifndef GL_FORGE_VERTEX_ARRAY_HPP
#define GL_FORGE_VERTEX_ARRAY_HPP

#include <glad/glad.h>
#include <span>

namespace glforge
{

class VertexArray
{
public:
    // Binds a vertex array at buffer_binding_point. Use this constructor for interleaved attributes.
    // vertex_layout specifies the sizes of the attributes.
    explicit VertexArray(std::span<const GLint> vertex_layout, GLuint buffer_binding_point = 0);

    // Binds a vertex array with multiple binding points, where the i-th attribute uses the i-th binding point.
    // vertex_layout specifies the sizes of the attributes.
    VertexArray(std::span<const GLint> vertex_layout, std::span<const GLuint> buffer_binding_points);

    VertexArray(const VertexArray&) = delete;
    VertexArray(VertexArray&& rhs) noexcept;
    VertexArray& operator=(const VertexArray&) = delete;
    VertexArray& operator=(VertexArray&& rhs) noexcept;
    ~VertexArray();

    [[nodiscard]] GLuint id() const noexcept;

    void bind();
    void bind_vertex_buffer(GLuint vbo, GLuint vertex_buffer_stride, GLuint buffer_binding_point = 0);
    void bind_index_buffer(GLuint ibo);

private:
    GLuint _id{0};
};

} // namespace glforge

#endif // GL_FORGE_VERTEX_ARRAY_HPP