#version 410 core

const int MAX_DIRECTIONAL_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 8;
const int MAX_POINT_LIGHTS = 8;

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

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;
    
    float linear;
    float quadratic;
};


struct SpotLight {
    vec3 direction;
    
    vec3 position;
    vec3 color;
    
    float linear;
    float quadratic;
    
    float cutOff;
};

uniform vec3 ambientLightColor;

uniform DirectionalLight[MAX_DIRECTIONAL_LIGHTS] directionalLights;
uniform SpotLight[MAX_SPOT_LIGHTS] spotLights;
uniform PointLight[MAX_POINT_LIGHTS] pointLights;

uniform int directionalLightsCount;
uniform int spotLightsCount;
uniform int pointLightsCount;


//vec4 CalcDirectionalLight(vec3 Normal)
//{
//    return CalcLightInternal(gDirectionalLight.Base, gDirectionalLight.Direction, Normal);
//}

//vec4 CalcPointLight(int Index, vec3 Normal)
//{
//    vec3 LightDirection = WorldPos0 - gPointLights[Index].Position;
//    float Distance = length(LightDirection);
//    LightDirection = normalize(LightDirection);
//
//    vec4 Color = CalcLightInternal(gPointLights[Index].Base, LightDirection, Normal);
//    float Attenuation = gPointLights[Index].Atten.Constant +
//    gPointLights[Index].Atten.Linear * Distance +
//    gPointLights[Index].Atten.Exp * Distance * Distance;
//
//    return Color / Attenuation;
//}

//vec4 CalcLightInternal(BaseLight Light, vec3 LightDirection, vec3 Normal)
//{
//    vec4 AmbientColor = vec4(Light.Color, 1.0f) * Light.AmbientIntensity;
//    float DiffuseFactor = dot(Normal, -LightDirection);
//
//    vec4 DiffuseColor = vec4(0, 0, 0, 0);
//    vec4 SpecularColor = vec4(0, 0, 0, 0);
//
//    if (DiffuseFactor > 0) {
//        DiffuseColor = vec4(Light.Color * Light.DiffuseIntensity * DiffuseFactor, 1.0f);
//        vec3 VertexToEye = normalize(gEyeWorldPos - WorldPos0);
//        vec3 LightReflect = normalize(reflect(LightDirection, Normal));
//        float SpecularFactor = dot(VertexToEye, LightReflect);
//        if (SpecularFactor > 0) {
//            SpecularFactor = pow(SpecularFactor, gSpecularPower);
//            SpecularColor = vec4(Light.Color * gMatSpecularIntensity * SpecularFactor, 1.0f);
//        }
//    }
//
//    return (AmbientColor + DiffuseColor + SpecularColor);
//}

vec3 specularColor(vec3 lightDir, vec3 viewDir, vec3 fragNormal, Material material) {
    float spec = 0.0;
//        blinn
        vec3 halfwayDir = normalize(lightDir + viewDir);
        if(dot(fragNormal, lightDir) > 0) {
            spec = pow(max(dot(fragNormal, halfwayDir), 0.0), material.shininess);
        }

    //    phong
//    vec3 reflectDir = reflect(lightDir, fragNormal);
//    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    
    return material.specular * spec;
}

vec3 diffuseColor(vec3 lightDir, vec3 fragNormal, vec3 lightColor, Material material) {
    float diff = max(dot(fragNormal, lightDir), 0.0);
    return material.diffuse * diff * lightColor;
}

vec3 calculateDirectionalLight(DirectionalLight light, Material material, vec3 sampledColor, vec3 fragNormal) {
    vec3 lightDir = normalize(- light.direction);
    vec3 viewDir = normalize(viewPos - fragPos);
    return specularColor(lightDir, viewDir, fragNormal, material) + sampledColor * diffuseColor(lightDir, fragNormal, light.color, material);
}

vec3 calculatePointLight(PointLight light, Material material, vec3 sampledColor, vec3 fragNormal) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (1.0 + light.linear * distance + light.quadratic * (distance * distance));
    
    return attenuation * (specularColor(lightDir, viewDir, fragNormal, material) + sampledColor * diffuseColor(lightDir, fragNormal, light.color, material));
}

vec3 calculateSpotLight(SpotLight light, Material material, vec3 sampledColor, vec3 fragNormal) {
    vec3 lightDir = - normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    
    float theta = dot(lightDir, normalize(-light.direction));
    
    vec3 value = vec3(0.0, 0.0, 0.0);
    if(theta > light.cutOff) {
        PointLight pointLight = PointLight(light.position, light.color, light.linear, light.quadratic);
        value = calculatePointLight(pointLight, material, sampledColor, fragNormal);
    }
    return value;
}

vec3 ambientColor(Material material, vec3 lightColor) {
    return material.ambient * lightColor;
}

void main(void) {
//    vec4 sampledColor = texture(material.diffuse0, fragTexCoord);
    vec4 sampledColor = vec4(0.3, 0.2, 0.5, 1.0);
    
    vec3 litColor = ambientColor(material, ambientLightColor);
    for (int i = 0 ; i < directionalLightsCount; i++) {
        litColor += calculateDirectionalLight(directionalLights[i], material, sampledColor.rgb, fragNormal);
    }
    
    for (int i = 0 ; i < pointLightsCount; i++) {
        litColor += calculatePointLight(pointLights[i], material, sampledColor.rgb, fragNormal);
    }

    for (int i = 0 ; i < spotLightsCount; i++) {
        litColor += calculateSpotLight(spotLights[i], material, sampledColor.rgb, fragNormal);
    }
    
    finalColor = vec4(litColor, sampledColor.a * material.dissolve);
}

//void main(void) {
////    vec3 lightDir = - normalize(light.position - fragPos);
//    vec3 lightDir = normalize(light.direction);
//    vec3 viewDir = normalize(viewPos - fragPos);
//    vec3 halfwayDir = normalize(lightDir + viewDir);
//    vec4 sampledColor = texture(material.diffuse0, fragTexCoord);
//
//    float spec = 0.0;
////    blinn
////    if(dot(fragNormal, lightDir) > 0) {
////        spec = pow(max(dot(fragNormal, halfwayDir), 0.0), material.shininess);
////    }
//
////    phong
//    vec3 reflectDir = reflect(lightDir, fragNormal);
//    spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//
//    vec3 specular = material.specular * spec;
//
//    float diff = max(dot(fragNormal, lightDir), 0.0);
//    vec3 diffuse = sampledColor.rgb * material.diffuse * diff * light.diffuse;
//
//    vec3 ambient = material.ambient * light.ambient;
//
//    vec3 result = specular + ambient + diffuse;
//    finalColor = vec4(result, sampledColor.a * material.dissolve);
//
//
////    vec4 TotalLight = CalcDirectionalLight(Normal);
////
////    for (int i = 0 ; i < gNumPointLights ; i++) {
////        TotalLight += CalcPointLight(i, Normal);
////    }
////
////    FragColor = texture2D(gSampler, TexCoord0.xy) * TotalLight;
//}
