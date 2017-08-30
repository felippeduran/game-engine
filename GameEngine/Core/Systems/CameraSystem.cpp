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
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"

using namespace entityx;
using namespace glm;

void CameraSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Camera, Transform>([this, &es, &events, dt] (Entity entity, Camera &camera, Transform &transform) {
        updateRenderers(es, events, dt, camera.projection, transform.localToWorldMatrix);
    });
};

void CameraSystem::updateRenderers(EntityManager &es, EventManager &events, TimeDelta dt, mat4& projection, mat4& view) {
    es.each<MeshRenderer, Transform>([dt, projection, view] (Entity entity, MeshRenderer &renderer, Transform &transform) {
        Material *material = renderer.material;
        material->program->use();
        
        material->program->setUniform("projection", projection);
        material->program->setUniform("view", view);
        material->program->setUniform("model", transform.localToWorldMatrix);
        if (material->texture) {
            material->program->setUniform("materialTex", 0); //set to 0 because the texture will be bound to GL_TEXTURE0
            
            //bind the texture
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, material->texture->object());
        }
        
        glBindVertexArray(renderer.vao);
        
        glDrawArrays(GL_TRIANGLES, 0, renderer.mesh->vertexCount);
        
        glBindVertexArray(0);
        if (material->texture) glBindTexture(GL_TEXTURE_2D, 0);
        material->program->stopUsing();
    });
}
