#ifndef GL_FORGE_INDEX_BUFFER_HPP
#define GL_FORGE_INDEX_BUFFER_HPP

#include <glad/glad.h>
#include <span>

namespace glforge
{

class IndexBuffer
{
public:
    explicit IndexBuffer(std::span<const std::uint32_t> indices);
    IndexBuffer(const IndexBuffer&) = delete;
    IndexBuffer(IndexBuffer&& rhs) noexcept;
    IndexBuffer& operator=(const IndexBuffer&) = delete;
    IndexBuffer& operator=(IndexBuffer&& rhs) noexcept;
    ~IndexBuffer();

    [[nodiscard]] GLuint id() const noexcept;
    [[nodiscard]] GLsizei num_indices() const noexcept;

private:
    GLuint _id{0};
    GLsizei _num_indices{0};
};

} // namespace glforge

#endif // GL_FORGE_INDEX_BUFFER_HPP