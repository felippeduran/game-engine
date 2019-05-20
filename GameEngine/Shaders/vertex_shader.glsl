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
    fragNormal = normalize(vec3(model * vec4(vertNormal, 0.0)));
    fragPos = vec3(model * vec4(vert, 1.0));
    gl_Position = projection * view * model * vec4(vert, 1.0);//w is 1.0, also notice cast to a vec4
}


//// returns intensity of reflected ambient lighting
//vec3 ambientLighting()
//{
//    return u_matAmbientReflectance * u_lightAmbientIntensity;
//}
//
//// returns intensity of diffuse reflection
//vec3 diffuseLighting(in vec3 N, in vec3 L)
//{
//    // calculation as for Lambertian reflection
//    float diffuseTerm = clamp(dot(N, L), 0, 1);
//    return u_matDiffuseReflectance * u_lightDiffuseIntensity * diffuseTerm;
//}
//
//// returns intensity of specular reflection
//vec3 specularLighting(in vec3 N, in vec3 L, in vec3 V)
//{
//    float specularTerm = 0;
//
//    // calculate specular reflection only if
//    // the surface is oriented to the light source
//    if(dot(N, L) > 0)
//    {
//        // half vector
//        vec3 H = normalize(L + V);
//        specularTerm = pow(dot(N, H), u_matShininess);
//    }
//    return u_matSpecularReflectance * u_lightSpecularIntensity * specularTerm;
//}
//
//void main(void)
//{
//    // normalize vectors after interpolation
//    vec3 L = normalize(o_toLight);
//    vec3 V = normalize(o_toCamera);
//    vec3 N = normalize(o_normal);
//
//    // get Blinn-Phong reflectance components
//    float Iamb = ambientLighting();
//    float Idif = diffuseLighting(N, L);
//    float Ispe = specularLighting(N, L, V);
//
//    // diffuse color of the object from texture
//    vec3 diffuseColor = texture(u_diffuseTexture, o_texcoords).rgb;
//
//    // combination of all components and diffuse color of the object
//    resultingColor.xyz = diffuseColor * (Iamb + Idif + Ispe);
//    resultingColor.a = 1;
//}
