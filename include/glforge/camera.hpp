#ifndef GL_FORGE_CAMERA_HPP
#define GL_FORGE_CAMERA_HPP

#include <glm/glm.hpp>

namespace glforge
{

enum class CameraMovement
{
    Forward,
    Backward,
    Left,
    Right,
    Up,
    Down,
};

class Camera
{
public:
    Camera() = default;
    Camera(const glm::vec3& position);
    /*
    The camera orientation and position are updated on
    the process_input functions.
    */
    void process_input(CameraMovement direction, float dt);
    void process_input(float x_offset, float y_offset);

    [[nodiscard]] const glm::vec3& gaze_direction() const noexcept;
    // view() should be called after process_input updates the camera position and orientation
    [[nodiscard]] glm::mat4 view() const noexcept;
    [[nodiscard]] const glm::vec3& position() const noexcept;

private:
    float _pitch{0.0f};
    float _yaw{0.0f};
    glm::vec3 _position{0.0f, 0.0f, 5.0f};
    glm::vec3 _right_dir{1.0f, 0.0f, 0.0f};
    glm::vec3 _gaze_dir{0.0f, 0.0f, -1.0f}; // Points to the negative z-axis direction
    float _speed{5.0f};
    float _mouse_sensitivity{0.1f};

    void update_orientation();
};

} // namespace glforge

#endif // GL_FORGE_CAMERA_HPP