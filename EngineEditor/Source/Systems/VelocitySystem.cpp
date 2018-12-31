//
//  VelocitySystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "VelocitySystem.h"
#include "Transform.h"
#include "Velocity.h"

using namespace entityx;
using namespace glm;
using namespace GameEngine;
using namespace GameEngine::Editor;

void VelocitySystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Transform, Velocity>([this, &es, &events, dt] (Entity entity, Transform &transform, Velocity &velocity) {
        vec3 direction = velocity.direction;
        if (dot(direction, direction) > FLT_EPSILON) direction = normalize(direction);
        transform.localPosition += vec3(transform.localToWorldMatrix * vec4(velocity.speed * direction * (float)dt, 0));
    });
};
