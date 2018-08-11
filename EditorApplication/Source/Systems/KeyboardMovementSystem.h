//
//  KeyboardMovementSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef KeyboardMovementSystem_h
#define KeyboardMovementSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

struct KeyboardMovementSystem : public entityx::System<KeyboardMovementSystem> {
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

#endif /* KeyboardMovementSystem_h */
