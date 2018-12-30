//
//  EditorCameraRotationSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "EditorCameraRotationSystem.h"
#include "Transform.h"
#include "EditorCamera.h"
#include "Rotatable.h"
#include "Mouse.h"
#include "Velocity2d.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace entityx;
using namespace glm;

void EditorCameraRotationSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<EditorCamera, Transform, Rotatable>([this, &es, &events, dt] (Entity entity, EditorCamera &camera, Transform &transform, Rotatable &rotatable) {
        es.each<Mouse, Velocity2d>([&es, dt, &transform] (Entity entity, Mouse &mouse, Velocity2d &velocity) {
            vec2 positionDelta = velocity.velocity * (float)dt;
            transform.localRotation = rotate(transform.localRotation, - positionDelta.x, vec3(0,1,0));
            transform.localRotation = rotate(transform.localRotation, - positionDelta.y, vec3(1,0,0));
        });
    });
};
