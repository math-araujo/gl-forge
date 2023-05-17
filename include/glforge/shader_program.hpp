#ifndef GL_FORGE_SHADER_PROGRAM_HPP
#define GL_FORGE_SHADER_PROGRAM_HPP

#include "shader.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <glm/matrix.hpp>
#include <span>
#include <string_view>
#include <unordered_map>

namespace glforge
{

class ShaderProgram
{
public:
    struct ShaderFile
    {
        std::filesystem::path path;
        Shader::Type type;
    };

    struct ShaderSource
    {
        std::string_view source;
        Shader::Type type;
    };

    ShaderProgram(std::span<const ShaderFile> shader_files);
    ShaderProgram(std::span<const ShaderSource> shader_sources);
    ShaderProgram(const ShaderProgram& rhs) = delete;
    ShaderProgram(ShaderProgram&& rhs) noexcept;
    ShaderProgram& operator=(const ShaderProgram& rhs) = delete;
    ShaderProgram& operator=(ShaderProgram&& rhs) noexcept;
    ~ShaderProgram();

    [[nodiscard]] GLuint id() const noexcept;
    void use() noexcept;

    void set_vec3(std::string_view uniform_name, const glm::vec3& vector);
    void set_mat4(std::string_view uniform_name, const glm::mat4& matrix);

private:
    struct heterogeneous_string_hash
    {
        using is_transparent = void;
        [[nodiscard]] std::size_t operator()(const std::string& key) const
        {
            return std::hash<std::string>{}(key);
        }

        [[nodiscard]] std::size_t operator()(std::string_view key) const
        {
            return std::hash<std::string_view>{}(key);
        }

        [[nodiscard]] std::size_t operator()(const char* key) const
        {
            return std::hash<const char*>{}(key);
        }
    };

    GLuint _id{0};
    std::unordered_map<std::string, GLint, heterogeneous_string_hash, std::equal_to<>> _uniform_locations;

    void get_active_uniforms();
};

ShaderProgram from_directory(std::filesystem::path shaders_directory);

} // namespace glforge

#endif // GL_FORGE_SHADER_PROGRAM_HPP