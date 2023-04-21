#include "shader_program.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace // anonymous
{

std::string load_shader_source_code(const std::filesystem::path& source_path)
{
    std::ifstream file{source_path.string()};
    if (!file.is_open())
    {
        throw std::runtime_error{std::format("File {} could not be opened\n", source_path.stem().string())};
    }

    std::stringstream stream;
    stream << file.rdbuf();
    return stream.str();
}

} // namespace

namespace glforge
{

ShaderProgram::ShaderProgram(std::span<BuildInfo> info) : _id{glCreateProgram()}
{
    assert(_id != 0);
    std::vector<Shader> shaders;
    shaders.reserve(info.size());

    for (const auto& [path, type] : info)
    {
        const std::string shader_source_code{load_shader_source_code(path)};
        shaders.emplace_back(shader_source_code, type);
        glAttachShader(_id, shaders.back().id());
    }

    glLinkProgram(_id);

    int link_success{0};
    glGetProgramiv(_id, GL_LINK_STATUS, &link_success);
    if (!link_success)
    {
        std::array<char, 1024> error_log{};
        glGetProgramInfoLog(_id, static_cast<GLsizei>(error_log.size()), nullptr, error_log.data());
        glDeleteProgram(_id);
        throw std::runtime_error{std::format("Shader program linking error.\nShader Program: {}\nError: {}\n",
                                             info.front().path.stem().string(), error_log.data())};
    }

    for (const Shader& shader : shaders)
    {
        glDetachShader(_id, shader.id());
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& rhs) noexcept : _id{rhs._id}
{
    rhs._id = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& rhs) noexcept
{
    std::swap(_id, rhs._id);
    return *this;
}

ShaderProgram::~ShaderProgram()
{
    if (_id)
    {
        glDeleteProgram(_id);
    }
}

GLuint ShaderProgram::id() const noexcept
{
    return _id;
}

void ShaderProgram::use() noexcept
{
    assert(_id != 0);
    glUseProgram(_id);
}

} // namespace glforge