#ifndef APP_H
#define APP_H

#include <window.h>
#include <renderer.h>
#include <camera.h>

class App{
private:
    Window window;
    Renderer renderer;
    Camera scene;
    bool running;

public:
    App(Window& _window, Renderer& _renderer, Camera& _scene);
    void init();
    void mainloop();
    void cleanup();
};

#endif