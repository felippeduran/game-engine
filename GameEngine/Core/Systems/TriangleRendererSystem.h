//
//  TriangleRendererSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 14/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef TriangleRendererSystem_h
#define TriangleRendererSystem_h

#include "TriangleRenderer.h"
#include "Transform.h"

using namespace entityx;

struct TriangleRendererSystem : public System<TriangleRendererSystem> {
    void update(EntityManager &es, EventManager &events, TimeDelta dt) override {
        es.each<TriangleRenderer, Transform>([dt] (Entity entity, TriangleRenderer &renderer, Transform &transform) {
            renderer.program->use();
            
            renderer.program->setUniform("model", transform.localToWorldMatrix);
            
            glBindVertexArray(renderer.VAO);
            
            glDrawArrays(GL_TRIANGLES, 0, 3);
            
            glBindVertexArray(0);
            renderer.program->stopUsing();
        });
    };
};

#endif /* TriangleRendererSystem_h */
