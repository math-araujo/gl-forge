// GLAD must be imported before GLFW
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glforge/application.hpp>
#include <glforge/window.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace glforge
{

struct Callbacks
{
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_movement_callback(GLFWwindow* window, double x_pos, double y_pos);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void scroll_callback(GLFWwindow* window, double x_offset, double y_offset);
};

Application::Application(int window_width, int window_height, std::string_view title) :
    _window{std::make_unique<Window>(window_width, window_height, title)}
{
    glfwSetWindowUserPointer(_window->get(), this);
    glfwSetWindowSizeCallback(_window->get(), Callbacks::framebuffer_size_callback);
    glfwSetKeyCallback(_window->get(), Callbacks::key_callback);
    glfwSetCursorPosCallback(_window->get(), Callbacks::mouse_movement_callback);
    glfwSetMouseButtonCallback(_window->get(), Callbacks::mouse_button_callback);
    glfwSetScrollCallback(_window->get(), Callbacks::scroll_callback);
    initialize_imgui();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
}

void Application::on_window_resize(int new_width, int new_height)
{
    glViewport(0, 0, new_width, new_height);
    _window->resize(new_width, new_height);
}

void Application::on_key_press(int key, int action)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_P)
        {
            _wireframe_mode = !_wireframe_mode;
            glPolygonMode(GL_FRONT_AND_BACK, _wireframe_mode ? GL_LINE : GL_FILL);
        }
    }
}

void Application::on_mouse_move(float x_pos, float y_pos)
{
    static bool first_mouse{true};
    static glm::vec2 last_position{0.0f, 0.0f};

    if (first_mouse)
    {
        last_position = {static_cast<float>(x_pos), static_cast<float>(y_pos)};
        first_mouse = false;
    }

    const float x_offset{static_cast<float>(x_pos - last_position.x)};
    const float y_offset{static_cast<float>(last_position.y - y_pos)};
    last_position = {static_cast<float>(x_pos), static_cast<float>(y_pos)};
    if (_mouse_pressed)
    {
        _camera.process_input(x_offset, y_offset);
    }
}

void Application::on_mouse_press(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        switch (action)
        {
        case GLFW_PRESS:
            _mouse_pressed = true;
            break;
        case GLFW_RELEASE:
            _mouse_pressed = false;
            break;
        default:
            break;
        }
    }
}

void Application::on_mouse_scroll(float /*x_offset*/, float y_offset)
{
    _zoom = std::max(std::min(_zoom - y_offset, 45.0f), 1.0f);
}

void Application::initialize_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io; // Use io in a statement to avoid unused variable warning
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(_window->get(), true);
    ImGui_ImplOpenGL3_Init("# version 460");
}

Application::~Application()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Application::run()
{
    float delta_time{0.0f};
    float previous_time{0.0f};

    while (!glfwWindowShouldClose(_window->get()))
    {
        const float current_time{static_cast<float>(glfwGetTime())};
        delta_time = current_time - previous_time;
        previous_time = current_time;

        process_input(delta_time);
        update(delta_time);
        render();
        glfwSwapBuffers(_window->get());
        glfwPollEvents();
    }
}

void Application::process_input(float delta_time)
{
    if (glfwGetKey(_window->get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window->get(), true);
        return;
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_W) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Forward, delta_time);
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_S) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Backward, delta_time);
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_D) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Right, delta_time);
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_A) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Left, delta_time);
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_E) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Up, delta_time);
    }

    if (glfwGetKey(_window->get(), GLFW_KEY_Q) == GLFW_PRESS)
    {
        _camera.process_input(CameraMovement::Down, delta_time);
    }
}

void Application::update(float /*delta_time*/)
{
}

void Application::render()
{
    glGetIntegerv(GL_VIEWPORT, _current_viewport.data());

    // Clear window with specified color
    glClearColor(0.0f, 0.1f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render scene...

    // Render GUI
    render_imgui_editor();
}

void Application::reset_viewport()
{
    glViewport(_current_viewport[0], _current_viewport[1], _current_viewport[2], _current_viewport[3]);
}

void Application::render_imgui_editor()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("FPS");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// Definitions for the static member functions used as GLFW callbacks
void Callbacks::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    auto app{static_cast<Application*>(glfwGetWindowUserPointer(window))};
    app->on_window_resize(width, height);
}

void Callbacks::key_callback(GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/)
{
    auto app{static_cast<Application*>(glfwGetWindowUserPointer(window))};
    app->on_key_press(key, action);
}

void Callbacks::mouse_movement_callback(GLFWwindow* window, double x_pos, double y_pos)
{
    auto app{static_cast<Application*>(glfwGetWindowUserPointer(window))};
    app->on_mouse_move(static_cast<float>(x_pos), static_cast<float>(y_pos));
}

void Callbacks::mouse_button_callback(GLFWwindow* window, int button, int action, int /*mods*/)
{
    auto app{static_cast<Application*>(glfwGetWindowUserPointer(window))};
    app->on_mouse_press(button, action);
}

void Callbacks::scroll_callback(GLFWwindow* window, double x_offset, double y_offset)
{
    auto app{static_cast<Application*>(glfwGetWindowUserPointer(window))};
    app->on_mouse_scroll(static_cast<float>(x_offset), static_cast<float>(y_offset));
}

} // namespace glforge