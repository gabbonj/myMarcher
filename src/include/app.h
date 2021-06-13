#ifndef APP_H
#define APP_H

#include <window.h>
#include <renderer.h>

class App{
private:
    Window window;
    Renderer renderer;
    bool running;

public:
    App(Window& _window, Renderer& _renderer);
    void init();
    void mainloop();
    void cleanup();
};

#endif