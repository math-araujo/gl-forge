#ifndef GL_FORGE_TEXTURE_SAMPLER_HPP
#define GL_FORGE_TEXTURE_SAMPLER_HPP

#include <glad/glad.h>

namespace glforge
{

struct SamplingParameters
{
    GLint wrap_s{GL_REPEAT};
    GLint wrap_t{GL_REPEAT};
    GLint wrap_r{GL_CLAMP_TO_EDGE};
    GLint min_filter{GL_LINEAR};
    GLint mag_filter{GL_LINEAR};
};

class TextureSampler
{
public:
    TextureSampler(const SamplingParameters& parameters = {});
    TextureSampler(const TextureSampler&) = delete;
    TextureSampler(TextureSampler&& rhs) noexcept;
    TextureSampler& operator=(const TextureSampler&) = delete;
    TextureSampler& operator=(TextureSampler&& rhs) noexcept;
    ~TextureSampler();

    [[nodiscard]] GLuint id() const noexcept;

private:
    GLuint _id;
};

} // namespace glforge

#endif // GL_FORGE_TEXTURE_SAMPLER_HPP