#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>


struct Light
{
    glm::vec3 position;
    float p1; // memory padding 
    glm::vec3 color;
    float brightness;

    Light(glm::vec3 _position, glm::vec3 _color, float _brightness) {
        position = _position;
        color = _color;
        brightness = _brightness;
    }
};


class Scene {
public:
    std::vector<Light> scene_lights;

    Scene();
    Scene(std::vector<Light> _scene_lights);
    void loadLights(std::vector<Light> _scene_lights);
    void addLight(Light light);
};

#endif