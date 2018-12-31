//
//  TransformSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 13/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef TransformSystem_h
#define TransformSystem_h

#include <entityx.h>

namespace GameEngine {
    struct TransformSystem : public entityx::System<TransformSystem> {
        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    };
};

#endif /* TransformSystem_h */
