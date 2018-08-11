//
//  KeyboardInputSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 11/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "KeyboardInputSystem.h"
#include "KeyboardInput.h"

using namespace entityx;
using namespace glm;

void KeyboardInputSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<KeyboardInput>([this, &es, &events, dt] (Entity entity, KeyboardInput &keyInput) {
        
//        es.get(<#Entity::Id id#>)
    });
};
