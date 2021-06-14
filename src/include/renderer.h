#ifndef RENDERER_H
#define RENDERER_H

#include <shader.h>
#include <camera.h>
#include <scene.h>
#include <glad/glad.h>

class Renderer{
private:
    unsigned int VBO, VAO, IBO;
    unsigned int step_location;
    unsigned int epsilon_location;
    unsigned int far_location;
    unsigned int shadow_intensity_location;
    unsigned int shadow_bias_location;
    unsigned int light_buffer_location;
    unsigned int light_number_location;
    unsigned int attenuation_location;
    unsigned int gamma_location;
    unsigned int shadow_k_location;

public:
    unsigned int inv_view_loc, inv_proj_loc;
    Shader marcher;
    Camera camera;
    Scene scene;
    int max_steps = 256;
    float epsilon = 0.001f;
    float far_distance = 100.0f;
    float shadow_intensity = 1.0f;
    float shadow_bias = 0.01f;
    glm::vec3 attenuation = glm::vec3(1.0f, 0.22f, 0.20f);
    float gamma = 2.2f;
    float shadow_k = 2.0f;
    
    Renderer(const char* _marcher_path, Camera& _camera, Scene& _scene);
    void initRender();
    void preRender();
    void render();
    void cleanupRender();
};

#endif