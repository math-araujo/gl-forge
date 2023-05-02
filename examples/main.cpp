#include <glforge/application.hpp>
#include <glforge/index_buffer.hpp>
#include <glforge/shader_program.hpp>
#include <glforge/vertex_array.hpp>
#include <glforge/vertex_buffer.hpp>
#include <glforge/window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

namespace glforge
{

namespace examples
{

class ExampleApp : public glforge::Application
{
public:
    using Application::Application; // Inherits base class constructor
    ~ExampleApp() override = default;

    void render() override
    {
        glGetIntegerv(GL_VIEWPORT, _current_viewport.data());

        // Clear window with specified color
        glClearColor(0.0f, 0.1f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const auto perspective{glm::perspective(glm::radians(_zoom), _window->aspect_ratio(), 0.01f, 100.0f)};
        const auto view{_camera.view()};
        program.use();
        program.set_mat4("mvp", perspective * view);
        program.set_vec3("color", glm::vec3{1.0f, 1.0f, 0.0f});

        vao.bind();
        /*vao.bind_vertex_buffer(vbo.id(), vbo.stride());
        glDrawArrays(GL_TRIANGLES, 0, 3);*/
        vao.bind_vertex_buffer(vbo_cube.id(), vbo_cube.stride());
        vao.bind_index_buffer(ibo_cube.id());
        glDrawElements(GL_TRIANGLES, ibo_cube.num_indices(), GL_UNSIGNED_INT, 0);
    }

private:
    std::vector<ShaderProgram::BuildInfo> info{{"test/vertex.vert", Shader::Type::Vertex},
                                               {"test/fragment.frag", Shader::Type::Fragment}};
    ShaderProgram program{info};
    VertexArray vao{std::vector<GLint>{3, 3, 2}};
    VertexBuffer vbo{std::vector<float>{-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
                                        1.0f,  0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.5f, 1.0f},
                     8};
    VertexBuffer vbo_cube{std::vector<float>{1.0,  1.0,  -1.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0,  -1.0, -1.0,
                                             1.0f, 1.0f, 0.0f, 0.0f, 0.5f, 1.0,  1.0,  1.0,  1.0f, 1.0f, 0.0f,
                                             0.0f, 0.5f, 1.0,  -1.0, 1.0,  1.0f, 1.0f, 0.0f, 0.0f, 0.5f, -1.0,
                                             1.0,  -1.0, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f, -1.0, -1.0, -1.0, 1.0f,
                                             1.0f, 0.0f, 0.0f, 0.5f, -1.0, 1.0,  1.0,  1.0f, 1.0f, 0.0f, 0.0f,
                                             0.5f, -1.0, -1.0, 1.0,  1.0f, 1.0f, 0.0f, 0.0f, 0.5f},
                          8};
    IndexBuffer ibo_cube{std::vector<std::uint32_t>{4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5,
                                                    4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1}};
};

} // namespace examples

} // namespace glforge

int main()
{
    try
    {
        auto example{std::make_unique<glforge::examples::ExampleApp>(1024, 768, "Example App")};
        example->run();
    }
    catch (const std::exception& exception)
    {
        std::cerr << exception.what() << '\n';
    }

    return 0;
}