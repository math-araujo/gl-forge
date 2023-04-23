// GLAD must be imported before GLFW
#include <glad/glad.h>

#include "window.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include <format>
#include <iostream>
#include <stdexcept>

namespace // anonymous
{

void error_callback(int error, const char* description)
{
    std::cerr << std::format("GLFW Error ({}): {}\n", error, description);
}

} // namespace

namespace glforge
{

Window::Window(int width, int height, std::string_view title) : _width{width}, _height{height}
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        throw std::runtime_error{"ERROR: Failed to initialize GLFW."};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 8);

    _window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (!_window)
    {
        glfwTerminate();
        throw std::runtime_error{"ERROR: Failed to create window and context."};
    }

    glfwMakeContextCurrent(_window);
    load_opengl();
}

void Window::load_opengl()
{
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        cleanup();
        throw std::runtime_error{"ERROR: Failed to initialize GLAD"};
    }
}

void Window::cleanup()
{
    if (_window)
    {
        glfwDestroyWindow(_window);
        glfwTerminate();
    }
}

Window::Window(Window&& rhs) noexcept : _width{rhs._width}, _height{rhs._height}, _window{rhs._window}
{
    rhs._window = nullptr;
}

Window& Window::operator=(Window&& rhs)
{
    std::swap(_width, rhs._width);
    std::swap(_height, rhs._height);
    std::swap(_window, rhs._window);
    return *this;
}

Window::~Window()
{
    cleanup();
}

int Window::width() const noexcept
{
    return _width;
}

int Window::height() const noexcept
{
    return _height;
}

float Window::aspect_ratio() const noexcept
{
    return static_cast<float>(_width) / _height;
}

const GLFWwindow* Window::get() const noexcept
{
    return _window;
}

GLFWwindow* Window::get() noexcept
{
    return _window;
}

void Window::resize(int width, int height)
{
    assert(width > 0);
    assert(height > 0);
    _width = width;
    _height = height;
}

} // namespace glforge