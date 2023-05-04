#include <algorithm>
#include <array>
#include <cassert>
#include <format>
#include <fstream>
#include <glforge/shader_program.hpp>
#include <glm/gtc/type_ptr.hpp>
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

ShaderProgram::ShaderProgram(std::span<ShaderFile> shader_files) : _id{glCreateProgram()}
{
    assert(_id != 0);
    std::vector<Shader> shaders;
    shaders.reserve(shader_files.size());

    for (const auto& [path, type] : shader_files)
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
                                             shader_files.front().path.stem().string(), error_log.data())};
    }

    for (const Shader& shader : shaders)
    {
        glDetachShader(_id, shader.id());
    }

    get_active_uniforms();
}

void ShaderProgram::get_active_uniforms()
{
    int num_uniforms{0};
    glGetProgramInterfaceiv(_id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &num_uniforms);
    std::array<GLenum, 2> properties{GL_NAME_LENGTH, GL_LOCATION};
    std::array<GLint, 2> results; // Store uniform name length at results[0] and uniform location at results[1]
    std::vector<char> uniform_name(256);
    for (int uniform = 0; uniform < num_uniforms; ++uniform)
    {
        glGetProgramResourceiv(_id, GL_UNIFORM, uniform, static_cast<GLsizei>(properties.size()), properties.data(),
                               static_cast<GLsizei>(results.size()), nullptr, results.data());
        uniform_name.resize(results[0]);
        glGetProgramResourceName(_id, GL_UNIFORM, uniform, static_cast<GLsizei>(uniform_name.size()), nullptr,
                                 uniform_name.data());
        const GLint uniform_location{results[1]};
        _uniform_locations.emplace(std::string{uniform_name.data(), uniform_name.size() - 1}, uniform_location);
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

void ShaderProgram::set_vec3(std::string_view uniform_name, const glm::vec3& vector)
{
    assert(_uniform_locations.contains(uniform_name));
    glProgramUniform3fv(_id, _uniform_locations.find(uniform_name)->second, 1, glm::value_ptr(vector));
}

void ShaderProgram::set_mat4(std::string_view uniform_name, const glm::mat4& matrix)
{
    assert(_uniform_locations.contains(uniform_name));
    glProgramUniformMatrix4fv(_id, _uniform_locations.find(uniform_name)->second, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace glforge