//
//  EditorCameraRotationEnableSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "EditorCameraRotationEnableSystem.h"
#include "MouseInput.h"
#include "Rotatable.h"
#include "EditorCamera.h"

using namespace entityx;
using namespace glm;
using namespace GameEngine::Editor;

void EditorCameraRotationEnableSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<MouseInput>([this, &es, &events, dt] (Entity entity, MouseInput &mouseInput) {
        if (mouseInput.key == 1) {
            if (mouseInput.state == 1) enableCameraRotation(es);
            else disableCameraRotation(es);
        }
    });
};

void EditorCameraRotationEnableSystem::enableCameraRotation(EntityManager &es) {
    es.each<EditorCamera>([this, &es] (Entity entity, EditorCamera &camera) {
        entity.assign<Rotatable>();
    });
}

void EditorCameraRotationEnableSystem::disableCameraRotation(EntityManager &es) {
    es.each<EditorCamera>([this, &es] (Entity entity, EditorCamera &camera) {
        entity.remove<Rotatable>();
    });
}
