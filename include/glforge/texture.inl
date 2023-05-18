#include <glforge/texture.hpp>

namespace glforge
{

template <typename T>
    requires std::integral<T> || std::floating_point<T>
void Texture::update(const ImageData<T>& image)
{
    assert(image.width <= _width);
    assert(image.height <= _height);
    glTextureSubImage2D(_id, image.level, 0, 0, image.width, image.height, image.format, image.type,
                        image.pixels.data());
}

} // namespace glforge