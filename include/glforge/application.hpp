#ifndef GL_FORGE_APPLICATION_HPP
#define GL_FORGE_APPLICATION_HPP

#include "camera.hpp"
#include <array>
#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <string_view>

namespace glforge
{

class Window;

class Application
{
public:
    Application(int window_width, int window_height, std::string_view title);
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    virtual ~Application();

    /*
    Call this member function to execute the application.
    This member function should not be redefined on derived classes.
    */
    void run();

protected:
    /*
    Core functionality of the application.
    Override these member functions to customize behaviour.
    */
    virtual void process_input(float delta_time);
    virtual void update(float delta_time);
    virtual void render();
    virtual void render_imgui_editor();

    /*
    Override these functions to react to GLFW callbacks.
    It's recommended to use/override the callbacks when the desired
    behaviour is to react to every event just once, instead of querying
    the key state like process_input member-function does.
    */
    virtual void on_window_resize(int new_width, int new_height);
    virtual void on_key_press(int key, int action);
    virtual void on_mouse_move(float x_pos, float y_pos);
    virtual void on_mouse_press(int button, int action);
    virtual void on_mouse_scroll(float x_offset, float y_offset);

    /*
    Reset viewport to the Application's width and height values
    */
    void reset_viewport();

    std::unique_ptr<Window> _window;
    std::array<int, 4> _current_viewport{};
    bool _wireframe_mode{false};
    bool _mouse_pressed{false};
    bool _free_mouse_move{false};
    float _zoom{45.0f};
    Camera _camera{};

private:
    friend struct Callbacks;

    /*
    Initializes ImGui
    */
    void initialize_imgui();
};

} // namespace glforge

#endif // GL_FORGE_APPLICATION_HPP