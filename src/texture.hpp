#ifndef GL_FORGE_TEXTURE_HPP
#define GL_FORGE_TEXTURE_HPP

#include <cstdint>
#include <glad/glad.h>

namespace glforge
{

struct TextureParameters
{
    GLenum target{GL_TEXTURE_2D};
    GLsizei mip_levels{1};
    GLenum internal_format{GL_RGBA8};
};

class Texture
{
public:
    Texture(std::uint32_t width, std::uint32_t height, const TextureParameters& parameters = {});
    Texture(const Texture&) = delete;
    Texture(Texture&& rhs) noexcept;
    Texture& operator=(const Texture&) = delete;
    Texture& operator=(Texture&& rhs) noexcept;
    ~Texture();

    [[nodiscard]] GLuint id() const noexcept;
    void bind(GLuint sampler, GLuint unit = 0);

private:
    GLuint _id{0};
    std::uint32_t _width{0};
    std::uint32_t _height{0};
};

} // namespace glforge

#endif // GL_FORGE_TEXTURE_HPP