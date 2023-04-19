#ifndef GL_FORGE_SHADER_HPP
#define GL_FORGE_SHADER_HPP

#include <glad/glad.h>
#include <string>

namespace glforge
{

class Shader
{
public:
    enum class Type : GLenum
    {
        Vertex = GL_VERTEX_SHADER,
        TessControl = GL_TESS_CONTROL_SHADER,
        TessEval = GL_TESS_EVALUATION_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER,
        Compute = GL_COMPUTE_SHADER
    };

    Shader(const std::string& shader_source_code, Type type);
    Shader(const Shader&) = delete;
    Shader(Shader&& rhs) noexcept;
    Shader& operator=(const Shader&) = delete;
    Shader& operator=(Shader&& rhs) noexcept;
    ~Shader();

    GLuint id() const noexcept;

private:
    GLuint _id{0};
};

const std::string& shader_typename(Shader::Type type);

} // namespace glforge

#endif // GL_FORGE_SHADER_HPP