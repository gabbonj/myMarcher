#ifndef SCENE_H
#define SCENE_H

#include <glm/glm.hpp>
#include <vector>


struct Light
{
    glm::vec3 position;
    glm::vec3 color;
    float brightness;
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