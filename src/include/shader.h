#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
public:
    unsigned int id;
    const char* vertexPath;
    const char* fragmentPath;

    Shader(const char* _vertexPath, const char* _fragmentPath);
    void use();
    void compile();

private:
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif