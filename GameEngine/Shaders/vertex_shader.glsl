#version 410 core

in vec3 vert;
in vec2 vertTexCoord;
in vec3 vertNormal;

out vec2 fragTexCoord;
out vec3 fragNormal;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;


void main() {
    fragTexCoord = vertTexCoord;
    fragNormal = vertNormal;
    fragPos = vec3(model * vec4(vert, 1.0));
    gl_Position = projection * view * model * vec4(vert, 1.0);//w is 1.0, also notice cast to a vec4
}
