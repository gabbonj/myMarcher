#include <app.h>

App::App(Window& _window, Renderer& _renderer, Camera& _scene) :
    window(_window), renderer(_renderer), scene(_scene), running(false) { }

void App::init() {
    running = true;
    window.windowInit();
}

void App::mainloop() {
    while (running) {
        running = window.windowUpdate();
    }
}

void App::cleanup() {
    window.windowCleanup();
}