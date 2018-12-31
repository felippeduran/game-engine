//
//  EditorCameraRotationSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef EditorCameraRotationSystem_h
#define EditorCameraRotationSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct EditorCameraRotationSystem : public entityx::System<EditorCameraRotationSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        };
    };
};

#endif /* EditorCameraRotationSystem_h */
