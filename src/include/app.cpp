#include <app.h>

App::App(Window& _window, Renderer& _renderer) :
    window(_window), renderer(_renderer), running(false) { }

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