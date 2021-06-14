#include <renderer.h>

Renderer::Renderer(const char* _marcher_path, Camera& _camera, Scene& _scene)
    : marcher(Shader("src\\shaders\\vertex.vs", _marcher_path)), camera(_camera), scene(_scene) {}

void Renderer::initRender() {
    glDisable(GL_DEPTH_TEST);

    float vertices[] = {
        1.0f,  1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f   
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    // setting the rendering quad
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    marcher.compile();

    // settinng the light buffer
    glGenBuffers(1, &light_buffer_location);
    glBindBuffer(GL_UNIFORM_BUFFER, light_buffer_location);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * scene.scene_lights.size(), NULL, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, light_buffer_location);

    step_location = glGetUniformLocation(marcher.id, "max_steps");
    epsilon_location = glGetUniformLocation(marcher.id, "epsilon");
    far_location = glGetUniformLocation(marcher.id, "far_distance");
    shadow_intensity_location = glGetUniformLocation(marcher.id, "shadow_intensity");
    shadow_bias_location = glGetUniformLocation(marcher.id, "shadow_bias");
    attenuation_location = glGetUniformLocation(marcher.id, "light_attenuation");
    light_number_location = glGetUniformLocation(marcher.id, "light_number");
    gamma_location = glGetUniformLocation(marcher.id, "gamma");
    shadow_k_location = glGetUniformLocation(marcher.id, "shadow_k");
}

void Renderer::preRender() {
    // setting the uniforms
    glUniform1i(step_location, max_steps);
    glUniform1f(epsilon_location, epsilon);
    glUniform1f(far_location, far_distance);
    glUniform1f(shadow_intensity_location, shadow_intensity);
    glUniform1f(shadow_bias_location, shadow_bias);
    glUniform1i(light_number_location, scene.scene_lights.size());
    glUniform3f(attenuation_location, attenuation.x, attenuation.y, attenuation.z);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Light) * scene.scene_lights.size(), &scene.scene_lights[0], GL_DYNAMIC_DRAW);
    glUniform1f(gamma_location, gamma);
    glUniform1f(shadow_k_location, shadow_k);
}

void Renderer::render() {
    //clearing the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // drawing the rendering quad
    marcher.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::cleanupRender() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}