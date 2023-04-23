#ifndef GL_FORGE_SHADER_PROGRAM_HPP
#define GL_FORGE_SHADER_PROGRAM_HPP

#include "shader.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <span>

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

private:
    GLuint _id{0};
};

ShaderProgram from_directory(std::filesystem::path shaders_directory);

} // namespace glforge

#endif // GL_FORGE_SHADER_PROGRAM_HPP