#ifndef GL_FORGE_SHADER_PROGRAM_HPP
#define GL_FORGE_SHADER_PROGRAM_HPP

#include "shader.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <span>
#include <unordered_map>

namespace glforge
{

class ShaderProgram
{
public:
    struct BuildInfo
    {
        std::filesystem::path path;
        Shader::Type type;
    };

    ShaderProgram(std::span<BuildInfo> info);
    ShaderProgram(const ShaderProgram& rhs) = delete;
    ShaderProgram(ShaderProgram&& rhs) noexcept;
    ShaderProgram& operator=(const ShaderProgram& rhs) = delete;
    ShaderProgram& operator=(ShaderProgram&& rhs) noexcept;
    ~ShaderProgram();

    [[nodiscard]] GLuint id() const noexcept;
    void use() noexcept;

    void set_vec3(const std::string& uniform_name, const glm::vec3& vector);
    void set_mat4(const std::string& uniform_name, const glm::mat4& matrix);

private:
    GLuint _id{0};
    std::unordered_map<std::string, GLint> _uniform_locations;

    void get_active_uniforms();
};

ShaderProgram from_directory(std::filesystem::path shaders_directory);

} // namespace glforge

#endif // GL_FORGE_SHADER_PROGRAM_HPP