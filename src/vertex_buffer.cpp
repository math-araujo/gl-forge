#include <algorithm>
#include <cassert>
#include <glforge/vertex_buffer.hpp>

namespace glforge
{

VertexBuffer::VertexBuffer(std::span<const float> buffer_data, GLuint stride) : _stride{stride}
{
    assert(_stride > 0);
    glCreateBuffers(1, &_id);
    glNamedBufferStorage(_id, buffer_data.size_bytes(), buffer_data.data(), GL_DYNAMIC_STORAGE_BIT);
}

VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept : _id{rhs._id}
{
    rhs._id = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    return *this;
}

VertexBuffer::~VertexBuffer()
{
    if (_id)
    {
        glDeleteBuffers(1, &_id);
    }
}

GLuint VertexBuffer::id() const noexcept
{
    return _id;
}

GLuint VertexBuffer::stride() const noexcept
{
    return _stride;
}

} // namespace glforge