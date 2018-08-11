#version 410 core

layout(location = 0) out vec4 finalColor;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragVert;

uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;

uniform sampler2D materialTex;

void main(void) {
    float dissolve = texture(materialTex, fragTexCoord).a;
    vec3 diffuseColor = materialDiffuse + texture(materialTex, fragTexCoord).rgb;
    vec3 ambientColor = materialAmbient + vec3(0.5, 0.5, 0.5) * materialDiffuse;
    vec3 specularColor = materialSpecular;
    
    finalColor = vec4(ambientColor + diffuseColor, dissolve);
}
