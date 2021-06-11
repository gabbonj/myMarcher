#include <iostream>
#include <app.h>

#include <glm/glm.hpp>

int main(int argc, char const *argv[])
{
    Camera camera(glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 0.0, 1.0));
    Renderer renderer("src\\shaders\\marcher.fs", camera);
    Window window(800, 600, "Marching", renderer);

    App app(window, renderer, camera);
    app.init();
    app.mainloop();
    app.cleanup();

    return 0;
}
