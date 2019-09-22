//
//  CameraSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 24/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "CameraSystem.h"
#include "Camera.h"
#include "Transform.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "format.h"

using namespace std;
using namespace entityx;
using namespace glm;
using namespace GameEngine;

void CameraSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Camera, Transform>([this, &es, &events, dt] (Entity entity, Camera &camera, Transform &transform) {
        mat4 worldToLocalMatrix = inverse(transform.localToWorldMatrix);
        mat4 projectionMatrix = camera.projection();
//        vec3 viewPosition = transform.localToWorldMatrix * vec4(transform.localPosition, 1.0f);
        updateRenderers(es, events, dt, projectionMatrix, worldToLocalMatrix, transform.localPosition);
    });
};

void CameraSystem::updateRenderers(EntityManager &es, EventManager &events, TimeDelta dt, mat4& projection, mat4& view, vec3& viewPosition) {
    es.each<MeshRenderer, Transform>([dt, &es, &projection, &view, &viewPosition] (Entity entity, MeshRenderer &renderer, Transform &transform) {
        Mesh *mesh = renderer.mesh;
        for (int i = (int)mesh->submeshes.size() - 1; i >=0; i--) {
            Submesh submesh = mesh->submeshes[i];
            Material *material = mesh->materials[submesh.materialId];
            material->program->use();
            
            if (material->program->hasUniform("projection")) material->program->setUniform("projection", projection);
            if (material->program->hasUniform("view")) material->program->setUniform("view", view);
            if (material->program->hasUniform("model")) material->program->setUniform("model", transform.localToWorldMatrix);
            if (material->program->hasUniform("viewPos")) material->program->setUniform("viewPos", viewPosition);
            
            if (material->program->hasUniform("viewPos")) {
                es.each<AmbientLight>([&material] (Entity entity, AmbientLight &light) {
                    material->program->setUniform("ambientLightColor", light.color);
                });
            }
            
            if (material->program->hasUniform("directionalLightsCount")) {
                int directionalLightIndex = 0;
                es.each<DirectionalLight, Transform>([&material, &directionalLightIndex] (Entity entity, DirectionalLight &light, Transform &lightTransform) {
                    material->program->setUniform(fmt::format("directionalLights[{0}].direction", directionalLightIndex).c_str(), lightTransform.forward());
                    material->program->setUniform(fmt::format("directionalLights[{0}].color", directionalLightIndex).c_str(), light.color);
                    directionalLightIndex++;
                });
                material->program->setUniform("directionalLightsCount", directionalLightIndex);
            }
            
            if (material->program->hasUniform("pointLightsCount")) {
                int pointLightIndex = 0;
                es.each<PointLight, Transform>([&material, &pointLightIndex] (Entity entity, PointLight &light, Transform &lightTransform) {
                    material->program->setUniform(fmt::format("pointLights[{0}].position", pointLightIndex).c_str(), lightTransform.localPosition);
                    material->program->setUniform(fmt::format("pointLights[{0}].color", pointLightIndex).c_str(), light.color);
                    material->program->setUniform(fmt::format("pointLights[{0}].linear", pointLightIndex).c_str(), light.linearAttenuation);
                    material->program->setUniform(fmt::format("pointLights[{0}].quadratic", pointLightIndex).c_str(), light.quadraticAttenuation);
                    pointLightIndex++;
                });
                material->program->setUniform("pointLightsCount", pointLightIndex);
            }
            
            if (material->program->hasUniform("spotLightsCount")) {
                int spotLightIndex = 0;
                es.each<SpotLight, Transform>([&material, &spotLightIndex] (Entity entity, SpotLight &light, Transform &lightTransform) {
                    material->program->setUniform(fmt::format("spotLights[{0}].position", spotLightIndex).c_str(), lightTransform.localPosition);
                    material->program->setUniform(fmt::format("spotLights[{0}].direction", spotLightIndex).c_str(), lightTransform.forward());
                    material->program->setUniform(fmt::format("spotLights[{0}].color", spotLightIndex).c_str(), light.color);
                    material->program->setUniform(fmt::format("spotLights[{0}].linear", spotLightIndex).c_str(), light.linearAttenuation);
                    material->program->setUniform(fmt::format("spotLights[{0}].quadratic", spotLightIndex).c_str(), light.quadraticAttenuation);
                    material->program->setUniform(fmt::format("spotLights[{0}].cutOff", spotLightIndex).c_str(), glm::cos(glm::radians(light.cutOff)));
                    spotLightIndex++;
                });
                material->program->setUniform("spotLightsCount", spotLightIndex);
            }
            
            unsigned int diffuseNr = 0;
            unsigned int specularNr = 0;
            unsigned int normalNr = 0;
            for (int i = 0; i < material->textures.size(); i++) {
                tdogl::Texture *texture = material->textures[i];
                TextureType type = material->textureTypes[i];
                if (type < TextureType::Count) {
                    glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
                    // retrieve texture number (the N in diffuse_textureN)
                    string number;
                    string name;
                    if (type == TextureType::Diffuse) {
                        number = to_string(diffuseNr++);
                        name = "diffuse";
                    }
                    if (type == TextureType::Specular) {
                        number = to_string(specularNr++);
                        name = "specular";
                    }
                    if (type == TextureType::Normal) {
                        number = to_string(normalNr++);
                        name = "normal";
                    }
                    
                    material->program->setUniform(("material." + name + number).c_str(), i);
                    glBindTexture(GL_TEXTURE_2D, texture->object());
                }
            }
            
            if (material->program->hasUniform("material.ambient")) material->program->setUniform("material.ambient", material->colorAmbient);
            if (material->program->hasUniform("material.diffuse")) material->program->setUniform("material.diffuse", material->colorDiffuse);
            if (material->program->hasUniform("material.specular")) material->program->setUniform("material.specular", material->colorSpecular);
            if (material->program->hasUniform("material.shininess")) material->program->setUniform("material.shininess", material->specularExponent);
            if (material->program->hasUniform("material.dissolve")) material->program->setUniform("material.dissolve", material->dissolve);
            
            glActiveTexture(GL_TEXTURE0);
            
            glBindVertexArray(mesh->shapeVAOs[i]);
            
            glDrawElements(GL_TRIANGLES, (GLsizei)submesh.size, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * submesh.offsetIBO));
            
            glBindVertexArray(0);
            material->program->stopUsing();
        }
    });
}
