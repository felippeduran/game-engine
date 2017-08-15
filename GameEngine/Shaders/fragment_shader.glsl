#version 410 core

layout(location = 0) out vec4 finalColor;

in vec4 fragColor;

void main(void) {
    finalColor = fragColor;
}
