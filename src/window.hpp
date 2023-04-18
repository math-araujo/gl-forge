#ifndef GL_FORGE_WINDOW_HPP
#define GL_FORGE_WINDOW_HPP

#include <string_view>

struct GLFWwindow;

namespace glforge
{

/*
Creates and holds an OpenGL context and GLFW window.
OpenGL resources should not be created, accessed or destroyed
without an active context i.e., before the creation of a Window
instance or after it's destruction.
*/
class Window
{
public:
    Window(int width, int height, std::string_view title);
    Window(const Window&) = delete;
    Window(Window&& rhs) noexcept;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&& rhs);
    ~Window();

    int width() const noexcept;
    int height() const noexcept;
    const GLFWwindow* get() const noexcept;
    GLFWwindow* get() noexcept;

    void resize(int width, int height);

private:
    int _width;
    int _height;
    GLFWwindow* _window;

    void load_opengl();
    void cleanup();
};

} // namespace glforge

#endif // GL_FORGE_WINDOW_HPP