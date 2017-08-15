//
//  TransformSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 13/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef TransformSystem_h
#define TransformSystem_h

#include "Transform.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

using namespace entityx;

struct TransformSystem : public System<TransformSystem> {
    void update(EntityManager &es, EventManager &events, TimeDelta dt) override {
        es.each<Transform, Position, Rotation, Scale, Parent>([dt] (Entity entity, Transform &transform, Position &position, Rotation &rotation, Scale &scale, Parent &parent) {
            glm::mat4 translationMatrix = glm::translate(position.localPosition);
            glm::mat4 rotationMatrix = glm::mat4_cast(rotation.localRotation);
            glm::mat4 scalingMatrix = glm::scale(scale.localScale);
            transform.modelMatrix = translationMatrix * rotationMatrix * scalingMatrix;
            
            glm::mat4 parentTransformMatrix;
            if (parent.parent.valid()) parentTransformMatrix = parent.parent.component<Transform>()->localToWorldMatrix;
            transform.localToWorldMatrix = parentTransformMatrix * (transform.modelMatrix);
//            worldToLocalMatrix = inverse(*localToWorldMatrix);
        });
    };
};

#endif /* TransformSystem_h */
