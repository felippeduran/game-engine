#version 410 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec4 vertColor;

out vec4 fragColor;

void main() {
    fragColor = vertColor;
    gl_Position = vec4(vert, 1.0);//w is 1.0, also notice cast to a vec4
}
