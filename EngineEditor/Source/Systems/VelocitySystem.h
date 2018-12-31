//
//  VelocitySystem.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef VelocitySystem_h
#define VelocitySystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct VelocitySystem : public entityx::System<VelocitySystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        };
    };
};

#endif /* VelocitySystem_h */
