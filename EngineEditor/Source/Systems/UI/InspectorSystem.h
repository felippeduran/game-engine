//
//  InspectorSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 28/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef InspectorSystem_h
#define InspectorSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct InspectorSystem : public entityx::System<InspectorSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        };
    };
};

#endif /* InspectorSystem_h */
