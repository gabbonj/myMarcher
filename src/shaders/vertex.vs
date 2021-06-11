#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 resolution;
out vec2 uv;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    uv = vec2(aPos.x * (resolution.x / resolution.y) , aPos.y);
}