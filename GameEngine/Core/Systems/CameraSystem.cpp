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
#include "DirectionalLight.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"

using namespace std;
using namespace entityx;
using namespace glm;

void CameraSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Camera, Transform>([this, &es, &events, dt] (Entity entity, Camera &camera, Transform &transform) {
        mat4 worldToLocalMatrix = inverse(transform.localToWorldMatrix);
        mat4 projectionMatrix = camera.projection();
        updateRenderers(es, events, dt, projectionMatrix, worldToLocalMatrix, transform.localPosition);
    });
};

void CameraSystem::updateRenderers(EntityManager &es, EventManager &events, TimeDelta dt, mat4& projection, mat4& view, vec3& viewPosition) {
    es.each<DirectionalLight, Transform>([dt, &es, &projection, &view, &viewPosition] (Entity entity, DirectionalLight &light, Transform &lightTransform) {
        es.each<MeshRenderer, Transform>([dt, &projection, &view, &viewPosition, &light, &lightTransform] (Entity entity, MeshRenderer &renderer, Transform &transform) {
            Mesh *mesh = renderer.mesh;
            for (int i = (int)mesh->submeshes.size() - 1; i >=0; i--) {
                Submesh submesh = mesh->submeshes[i];
                Material *material = mesh->materials[submesh.materialId];
                material->program->use();
                
                material->program->setUniform("projection", projection);
                material->program->setUniform("view", view);
                material->program->setUniform("model", transform.localToWorldMatrix);
                material->program->setUniform("viewPos", viewPosition);
                
                material->program->setUniform("light.position", lightTransform.localPosition);
                material->program->setUniform("light.direction", lightTransform.forward());
                material->program->setUniform("light.ambient", light.ambient);
                material->program->setUniform("light.diffuse", light.diffuse);
                material->program->setUniform("light.specular", light.specular);
                
                unsigned int diffuseNr = 0;
                unsigned int specularNr = 0;
                unsigned int normalNr = 0;
                for (int i = 0; i < material->textures.size(); i++)
                {
                    tdogl::Texture *texture = material->textures[i];
                    TextureType type = material->textureTypes[i];
                    
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
                
                material->program->setUniform("material.ambient", material->colorAmbient);
                material->program->setUniform("material.diffuse", material->colorDiffuse);
                material->program->setUniform("material.specular", material->colorSpecular);
                material->program->setUniform("material.shininess", material->specularExponent);
                material->program->setUniform("material.dissolve", material->dissolve);
                
                glActiveTexture(GL_TEXTURE0);
                
                glBindVertexArray(mesh->shapeVAOs[i]);
                
                glDrawElements(GL_TRIANGLES, (GLsizei)submesh.size, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * submesh.offsetIBO));
                
                glBindVertexArray(0);
                material->program->stopUsing();
            }
        });
    });
}
