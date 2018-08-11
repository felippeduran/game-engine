//
//  InputCleanupSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "InputCleanupSystem.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "MouseEnter.h"
#include "MousePositionEvent.h"
#include "MouseScrollPositionEvent.h"

using namespace entityx;
using namespace glm;

void InputCleanupSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<KeyboardInput>([this, &es, &events, dt] (Entity entity, KeyboardInput &keyInput) {
        entity.destroy();
    });
    
    es.each<MouseInput>([this, &es, &events, dt] (Entity entity, MouseInput &mouseInput) {
        entity.destroy();
    });
    
    es.each<MouseEnter>([this, &es, &events, dt] (Entity entity, MouseEnter &mouseEnter) {
        entity.destroy();
    });
    
    es.each<MousePositionEvent>([this, &es, &events, dt] (Entity entity, MousePositionEvent &mousePositionEvent) {
        entity.destroy();
    });
    
    es.each<MouseScrollPositionEvent>([this, &es, &events, dt] (Entity entity, MouseScrollPositionEvent &mouseScrollPosition) {
        entity.destroy();
    });
};
