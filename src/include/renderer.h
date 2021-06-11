#ifndef RENDERER_H
#define RENDERER_H

#include <shader.h>
#include <camera.h>
#include <glad/glad.h>

class Renderer{
private:
    unsigned int VBO, VAO, IBO;
    unsigned int step_location;
    unsigned int epsilon_location;
    unsigned int far_location;

public:
    unsigned int inv_view_loc, inv_proj_loc;
    Shader marcher;
    Camera camera;
    int max_steps = 64;
    float epsilon = 0.001f;
    float far_distance = 100.0f;
    
    Renderer(const char* _marcher_path, Camera& _scene);
    void initRender();
    void preRender();
    void render();
    void cleanupRender();
};

#endif