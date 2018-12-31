//
//  EditorCameraRotationEnableSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef EditorCameraRotationEnableSystem_h
#define EditorCameraRotationEnableSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct EditorCameraRotationEnableSystem : public entityx::System<EditorCameraRotationEnableSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
            
        private:
            void enableCameraRotation(entityx::EntityManager &es);
            void disableCameraRotation(entityx::EntityManager &es);
        };
    };
};

#endif /* EditorCameraRotationEnableSystem_h */
