#include <algorithm>
#include <cassert>
#include <glforge/vertex_array.hpp>

namespace glforge
{

VertexArray::VertexArray(std::span<const GLint> vertex_layout, GLuint buffer_binding_point)
{
    glCreateVertexArrays(1, &_id);
    assert(_id != 0);

    GLuint offset{0};
    for (GLuint index = 0; GLint attribute_size : vertex_layout)
    {
        glEnableVertexArrayAttrib(_id, index);
        glVertexArrayAttribFormat(_id, index, attribute_size, GL_FLOAT, false, offset * sizeof(float));
        glVertexArrayAttribBinding(_id, index, buffer_binding_point);
        offset += attribute_size;
        ++index;
    }
}

VertexArray::VertexArray(std::span<const GLint> vertex_layout, std::span<const GLuint> buffer_binding_points)
{
    glCreateVertexArrays(1, &_id);
    assert(_id != 0);

    const GLuint num_attributes{static_cast<GLuint>(vertex_layout.size())};
    for (GLuint index = 0; index < num_attributes; ++index)
    {
        glEnableVertexArrayAttrib(_id, index);
        glVertexArrayAttribFormat(_id, index, vertex_layout[index], GL_FLOAT, false, 0);
        glVertexArrayAttribBinding(_id, index, buffer_binding_points[index]);
    }
}

VertexArray::VertexArray(VertexArray&& rhs) noexcept : _id{rhs._id}
{
    rhs._id = 0;
}

VertexArray& VertexArray::operator=(VertexArray&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    return *this;
}

VertexArray::~VertexArray()
{
    if (_id)
    {
        glDeleteVertexArrays(1, &_id);
    }
}

GLuint VertexArray::id() const noexcept
{
    return _id;
}

void VertexArray::bind()
{
    assert(_id != 0);
    glBindVertexArray(_id);
}

void VertexArray::bind_vertex_buffer(GLuint vbo, GLuint vertex_buffer_stride, GLuint buffer_binding_point)
{
    glVertexArrayVertexBuffer(_id, buffer_binding_point, vbo, 0, vertex_buffer_stride * sizeof(float));
}

void VertexArray::bind_index_buffer(GLuint ibo)
{
    glVertexArrayElementBuffer(_id, ibo);
}

} // namespace glforge