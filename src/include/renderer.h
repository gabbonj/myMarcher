#ifndef RENDERER_H
#define RENDERER_H

#include <shader.h>
#include <camera.h>
#include <glad/glad.h>

class Renderer{
private:
    unsigned int VBO, VAO, IBO;

public:
    unsigned int inv_view_loc, inv_proj_loc;
    Shader marcher;
    Camera camera;
    
    Renderer(const char* _marcher_path, Camera& _scene);
    void initRender();
    void preRender();
    void render();
    void cleanupRender();
};

#endif