#include "texture.hpp"
#include <algorithm>
#include <cassert>

namespace glforge
{

Texture::Texture(GLsizei width, GLsizei height, const TextureParameters& parameters) : _width{width}, _height{height}
{
    assert(_width > 0);
    assert(_height > 0);
    glCreateTextures(parameters.target, 1, &_id);
    assert(_id != 0);
    glTextureStorage2D(_id, parameters.mip_levels, parameters.internal_format, _width, _height);
}

Texture::Texture(Texture&& rhs) noexcept : _id{rhs._id}, _width{rhs._width}, _height{rhs._height}
{
    rhs._id = 0;
}

Texture& Texture::operator=(Texture&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    std::swap(_width, rhs._width);
    std::swap(_height, rhs._height);
    return *this;
}

Texture::~Texture()
{
    if (_id)
    {
        glDeleteTextures(1, &_id);
    }
}

GLuint Texture::id() const noexcept
{
    return _id;
}

void Texture::bind(GLuint sampler, GLuint unit)
{
    glBindSampler(unit, sampler);
    glBindTextureUnit(unit, _id);
}

void Texture::update(const ImageData& image)
{
    assert(image.width <= _width);
    assert(image.height <= _height);
    glTextureSubImage2D(_id, image.level, 0, 0, image.width, image.height, image.format, image.type,
                        image.pixels.data());
}

} // namespace glforge