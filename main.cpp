#include <iostream>
#include <app.h>
#include <vector>

#include <glm/glm.hpp>


int main(int argc, char const *argv[])
{
    std::vector<Light> lights = {
        Light(glm::vec3(-2.0, 3.0, -3.0), glm::vec3(1.0, 1.0, 1.0), 0.6f),
        Light(glm::vec3(2.0, -3.0, -3.0), glm::vec3(1.0, 0.67, 0.0), 1.0)
    };
    Scene scene(lights);
    Camera camera(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 0.0, 1.0));
    Renderer renderer("src\\shaders\\marcher.fs", camera, scene);
    Window window(800, 600, "Marching", renderer);

    App app(window, renderer);
    app.init();
    app.mainloop();
    app.cleanup();

    return 0;
}
