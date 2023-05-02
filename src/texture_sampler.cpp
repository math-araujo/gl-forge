#include <algorithm>
#include <cassert>
#include <glforge/texture_sampler.hpp>

namespace glforge
{

TextureSampler::TextureSampler(const SamplingParameters& parameters)
{
    glCreateSamplers(1, &_id);
    assert(_id != 0);
    glSamplerParameteri(_id, GL_TEXTURE_WRAP_S, parameters.wrap_s);
    glSamplerParameteri(_id, GL_TEXTURE_WRAP_T, parameters.wrap_t);
    glSamplerParameteri(_id, GL_TEXTURE_WRAP_R, parameters.wrap_r);
    glSamplerParameteri(_id, GL_TEXTURE_MIN_FILTER, parameters.min_filter);
    glSamplerParameteri(_id, GL_TEXTURE_MAG_FILTER, parameters.mag_filter);
}

TextureSampler::TextureSampler(TextureSampler&& rhs) noexcept : _id{rhs._id}
{
    rhs._id = 0;
}

TextureSampler& TextureSampler::operator=(TextureSampler&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    return *this;
}

TextureSampler::~TextureSampler()
{
    if (_id)
    {
        glDeleteSamplers(1, &_id);
    }
}

GLuint TextureSampler::id() const noexcept
{
    return _id;
}

} // namespace glforge