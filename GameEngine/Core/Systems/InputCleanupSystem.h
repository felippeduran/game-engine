//
//  InputCleanupSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef InputCleanupSystem_h
#define InputCleanupSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    struct InputCleanupSystem : public entityx::System<InputCleanupSystem> {
        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };
};

#endif /* InputCleanupSystem_h */
