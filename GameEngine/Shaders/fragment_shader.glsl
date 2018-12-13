#version 410 core

layout(location = 0) out vec4 finalColor;

in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

uniform vec3 viewPos;

struct Material {
    sampler2D diffuse0;
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
    float dissolve;
};

uniform Material material;

struct Light {
    vec3 position;
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main(void) {
    vec3 lightDir = - normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    vec4 sampledColor = texture(material.diffuse0, fragTexCoord);

    float spec = 0.0;
//    blinn
//    if(dot(fragNormal, lightDir) > 0) {
//        spec = pow(max(dot(fragNormal, halfwayDir), 0.0), material.shininess);
//    }

//    phong
    vec3 reflectDir = reflect(lightDir, fragNormal);
    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    vec3 specular = material.specular * spec;
    
    float diff = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = sampledColor.rgb * material.diffuse * diff * light.diffuse;
    
    vec3 ambient = material.ambient * light.ambient;

    vec3 result = specular + ambient + diffuse;
    finalColor = vec4(result, sampledColor.a * material.dissolve);
}
