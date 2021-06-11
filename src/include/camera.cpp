#include <camera.h>

Camera::Camera() : camera_position(glm::vec3(0.0)), camera_forward(glm::vec3(0.0, 0.0, 1.0)) {
    updateCamera(camera_position, camera_forward);
    pitch = 0;
    yaw = 0;
    rotateCamera(pitch, yaw);
}

Camera::Camera(glm::vec3 _camera_position, glm::vec3 _camera_forward)
    : camera_position(_camera_position), camera_forward(_camera_forward) {
    updateCamera(camera_position, camera_forward);
    pitch = glm::asin(camera_forward.y);
    yaw = glm::atan(camera_forward.z, camera_forward.x);
}

void Camera::updateCamera(glm::vec3 _camera_position, glm::vec3 _camera_forward) {
    camera_position = _camera_position;
    camera_forward = _camera_forward;
    //rimettere camera_position
    invers_view = glm::inverse(glm::lookAt(camera_position, camera_position + camera_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Camera::setCameraPosition(glm::vec3 _position) {
    updateCamera(_position, camera_forward);
}

void Camera::rotateCamera(float _pitch, float _yaw) {
    pitch = glm::clamp(_pitch, -3.14f/2.0f, 3.14f/2.0f);
    yaw = _yaw;
    camera_forward = glm::vec3(
        glm::cos(yaw) * glm::cos(pitch),
        glm::sin(pitch),
        glm::sin(yaw) * glm::cos(pitch)
    );
    updateCamera(camera_position, glm::normalize(camera_forward));
}


