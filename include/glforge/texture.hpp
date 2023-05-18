#ifndef GL_FORGE_TEXTURE_HPP
#define GL_FORGE_TEXTURE_HPP

#include <concepts>
#include <glad/glad.h>
#include <span>

namespace glforge
{

struct TextureParameters
{
    GLenum target{GL_TEXTURE_2D};
    GLsizei mip_levels{1};
    GLenum internal_format{GL_RGBA8};
};

template <typename T>
struct ImageData
{
    GLint level{0};
    GLsizei width;
    GLsizei height;
    GLenum format{GL_RGBA};
    GLenum type{GL_UNSIGNED_BYTE};
    std::span<const T> pixels;
};

class Texture
{
public:
    Texture(GLsizei width, GLsizei height, const TextureParameters& parameters = {});
    Texture(const Texture&) = delete;
    Texture(Texture&& rhs) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& rhs) noexcept;
    ~Texture();

    [[nodiscard]] GLuint id() const noexcept;
    void bind(GLuint sampler, GLuint unit = 0);

    template <typename T>
        requires std::integral<T> || std::floating_point<T>
    void update(const ImageData<T>& image);

private:
    GLuint _id{0};
    GLsizei _width{0};
    GLsizei _height{0};
};

} // namespace glforge

#include "texture.inl"

#endif // GL_FORGE_TEXTURE_HPP