#include <renderer.h>

Renderer::Renderer(const char* _marcher_path, Camera& _scene)
    : marcher(Shader("src\\shaders\\vertex.vs", _marcher_path)), camera(_scene){}

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

    step_location = glGetUniformLocation(marcher.id, "max_steps");
    epsilon_location = glGetUniformLocation(marcher.id, "epsilon");
    far_location = glGetUniformLocation(marcher.id, "far_distance");
    shadow_intensity_location = glGetUniformLocation(marcher.id, "shadow_intensity");
    shadow_bias_location = glGetUniformLocation(marcher.id, "shadow_bias");
}

void Renderer::preRender() {
    glUniform1i(step_location, max_steps);
    glUniform1f(epsilon_location, epsilon);
    glUniform1f(far_location, far_distance);
    glUniform1f(shadow_intensity_location, shadow_intensity);
    glUniform1f(shadow_bias_location, shadow_bias);
}

void Renderer::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    marcher.use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::cleanupRender() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
}