#include <scene.h>

Scene::Scene() {}

Scene::Scene(std::vector<Light> _scene_lights) : scene_lights(_scene_lights) {}

void Scene::loadLights(std::vector<Light> _scene_lights) {
    for (Light l : _scene_lights) {
        scene_lights.push_back(l);
    }
}

void Scene::addLight(Light light) {
    scene_lights.push_back(light);
}