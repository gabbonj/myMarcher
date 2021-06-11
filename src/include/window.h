#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <renderer.h>


class Window{
private:
    int height;
    int width;
    Renderer renderer;
    std::string name;
    unsigned int resolution_loc;
    double time = 0;
    double delta_time;
    double current_time;
    
public:
    GLFWwindow* window;
    
    Window(unsigned int _height, unsigned int _width, std::string _name, Renderer& _render);
    void processInput();
    void windowInit();
    bool windowUpdate();
    void windowCleanup();

    void guiInit();
    void guiPreUpdate();
    void guiUpdate();
    void guiCleanup();
};

#endif