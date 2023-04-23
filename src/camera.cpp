#include "camera.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

namespace glforge
{

Camera::Camera(const glm::vec3& position) : _position{position}
{
    update_orientation();
}

void Camera::process_input(CameraMovement direction, float dt)
{
    if (direction == CameraMovement::Forward)
    {
        _position += _gaze_dir * _speed * dt;
    }

    if (direction == CameraMovement::Backward)
    {
        _position -= _gaze_dir * _speed * dt;
    }

    if (direction == CameraMovement::Right)
    {
        _position += _right_dir * _speed * dt;
    }

    if (direction == CameraMovement::Left)
    {
        _position -= _right_dir * _speed * dt;
    }

    if (direction == CameraMovement::Up)
    {
        _position.y += _speed * dt;
    }

    if (direction == CameraMovement::Down)
    {
        _position.y -= _speed * dt;
    }
}

void Camera::update_orientation()
{
    const float rad_pitch{glm::radians(_pitch)};
    const float rad_yaw{glm::radians(_yaw)};
    // clang-format off
    _gaze_dir = glm::normalize(glm::vec3{
                glm::cos(rad_pitch) * glm::sin(rad_yaw), 
                glm::sin(rad_pitch),
                -1.0f * glm::cos(rad_pitch) * glm::cos(rad_yaw)
            });
    // clang-format on
    _right_dir = glm::normalize(glm::cross(_gaze_dir, glm::vec3{0.0f, 1.0f, 0.0f}));
}

const glm::vec3& Camera::gaze_direction() const noexcept
{
    return _gaze_dir;
}

void Camera::process_input(float x_offset, float y_offset)
{
    _yaw += x_offset * _mouse_sensitivity;
    _pitch += y_offset * _mouse_sensitivity;
    _pitch = std::clamp(_pitch, -89.9f, 89.9f);
    update_orientation();
}

glm::mat4 Camera::view() const noexcept
{
    return glm::lookAt(_position, _position + _gaze_dir, glm::vec3{0.0f, 1.0f, 0.0f});
}

const glm::vec3& Camera::position() const noexcept
{
    return _position;
}

} // namespace glforge