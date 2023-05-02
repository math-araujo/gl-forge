#include <algorithm>
#include <cassert>
#include <glforge/index_buffer.hpp>

namespace glforge
{

IndexBuffer::IndexBuffer(std::span<const std::uint32_t> indices) : _num_indices{static_cast<GLsizei>(indices.size())}
{
    glCreateBuffers(1, &_id);
    assert(_id != 0);
    glNamedBufferStorage(_id, indices.size_bytes(), indices.data(), GL_DYNAMIC_STORAGE_BIT);
}

IndexBuffer::IndexBuffer(IndexBuffer&& rhs) noexcept : _id{rhs._id}, _num_indices{rhs._num_indices}
{
    rhs._id = 0;
}

IndexBuffer& IndexBuffer::operator=(IndexBuffer&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    std::swap(_num_indices, rhs._num_indices);
    return *this;
}

IndexBuffer::~IndexBuffer()
{
    if (_id)
    {
        glDeleteBuffers(1, &_id);
    }
}

GLuint IndexBuffer::id() const noexcept
{
    return _id;
}

GLsizei IndexBuffer::num_indices() const noexcept
{
    return _num_indices;
}

} // namespace glforge