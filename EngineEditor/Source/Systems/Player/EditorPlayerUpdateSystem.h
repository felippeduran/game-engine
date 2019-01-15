//
//  EditorPlayerUpdateSystem.h
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef EditorPlayerUpdateSystem_h
#define EditorPlayerUpdateSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct EditorPlayerUpdateSystem : public entityx::System<EditorPlayerUpdateSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        };
    };
};

#endif /* EditorPlayerUpdateSystem_h */
