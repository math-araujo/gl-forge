#include "shader.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <format>
#include <stdexcept>
#include <string_view>
#include <unordered_map>

namespace glforge
{

Shader::Shader(std::string_view shader_source_code, Type type) : _id{glCreateShader(static_cast<GLenum>(type))}
{
    assert(_id != 0);
    const GLchar* source_code_ptr{shader_source_code.data()};
    glShaderSource(_id, 1, &source_code_ptr, nullptr);
    glCompileShader(_id);

    int compilation_successful{0};
    glGetShaderiv(_id, GL_COMPILE_STATUS, &compilation_successful);

    if (!compilation_successful)
    {
        std::array<char, 1024> error_log{};
        glGetShaderInfoLog(_id, static_cast<GLsizei>(error_log.size()), nullptr, error_log.data());
        glDeleteShader(_id);
        throw std::runtime_error{
            std::format("{} Shader compilation error: {}\n", shader_typename(type), error_log.data())};
    }
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