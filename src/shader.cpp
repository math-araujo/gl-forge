#include "shader.hpp"
#include <algorithm>
#include <array>
#include <format>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace // anonymous
{

void check_shader_compilation(GLuint shader_id, std::string_view shader_type);

}

namespace glforge
{

Shader::Shader(const std::string& shader_source_code, Type type) : _id{glCreateShader(static_cast<GLenum>(type))}
{
    const char* source_code_ptr{shader_source_code.c_str()};
    glShaderSource(_id, 1, &source_code_ptr, nullptr);
    glCompileShader(_id);
    check_shader_compilation(_id, shader_typename(type));
}

const std::string& shader_typename(Shader::Type type)
{
    static const std::unordered_map<Shader::Type, std::string> shader_types = {
        {Shader::Type::Vertex, "Vertex"},
        {Shader::Type::TessControl, "Tessellation Control"},
        {Shader::Type::TessEval, "Tessellation Evaluation"},
        {Shader::Type::Fragment, "Fragment"},
        {Shader::Type::Compute, "Compute"},
    };

    return shader_types.at(type);
}

Shader::Shader(Shader&& rhs) noexcept : _id{rhs._id}
{
    rhs._id = 0;
}

Shader& Shader::operator=(Shader&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    return *this;
}

Shader::~Shader()
{
    if (_id)
    {
        glDeleteShader(_id);
    }
}

GLuint Shader::id() const noexcept
{
    return _id;
}

} // namespace glforge

namespace // anonymous
{

void check_shader_compilation(GLuint shader_id, std::string_view shader_type)
{
    int compilation_successful{0};
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_successful);

    if (!compilation_successful)
    {
        std::array<char, 1024> error_log{};
        glGetShaderInfoLog(shader_id, static_cast<GLsizei>(error_log.size()), nullptr, error_log.data());
        throw std::runtime_error{std::format("{} Shader compilation error: {}\n", shader_type, error_log.data())};
    }
}

} // namespace