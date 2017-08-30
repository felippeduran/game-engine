#version 410 core

layout(location = 0) out vec4 finalColor;

in vec4 fragColor;
in vec3 fragNormal;
in vec3 fragVert;

void main(void) {
    finalColor = fragColor;
}
