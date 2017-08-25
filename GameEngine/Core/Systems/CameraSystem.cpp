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
#include "TriangleRenderer.h"

using namespace entityx;
using namespace glm;

void CameraSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    std::cout << "CameraSystem" << std::endl;
    es.each<Camera, Transform>([this, &es, &events, dt] (Entity entity, Camera &camera, Transform &transform) {
        updateRenderers(es, events, dt, camera.projection, transform.localToWorldMatrix);
    });
};

void CameraSystem::updateRenderers(EntityManager &es, EventManager &events, TimeDelta dt, mat4& projection, mat4& view) {
    es.each<TriangleRenderer, Transform>([dt, projection, view] (Entity entity, TriangleRenderer &renderer, Transform &transform) {
        renderer.program->use();
        
        renderer.program->setUniform("projection", projection);
        renderer.program->setUniform("view", view);
        renderer.program->setUniform("model", transform.localToWorldMatrix);
        
        glBindVertexArray(renderer.VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
        renderer.program->stopUsing();
    });
}
