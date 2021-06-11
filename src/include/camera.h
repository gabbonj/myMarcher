#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
public:
    glm::vec3 camera_position;
    glm::vec3 camera_forward;
    glm::mat4 invers_view;
    glm::mat4 invers_proj;
    float pitch;
    float yaw;
    

    Camera();
    Camera(glm::vec3 _camera_position, glm::vec3 _camera_forward);

    void setCameraPosition(glm::vec3 position);
    void rotateCamera(float pitch, float yaw);

private:
    void updateCamera(glm::vec3 _camera_position, glm::vec3 _camera_forward);
};

#endif