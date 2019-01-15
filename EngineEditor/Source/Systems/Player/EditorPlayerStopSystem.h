//
//  EditorPlayerStopSystem.h
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef EditorPlayerStopSystem_h
#define EditorPlayerStopSystem_h

#include <entityx.h>

namespace GameEngine {
    class InputHandler;
    
    namespace Editor {
        struct EditorPlayerStopSystem : public entityx::System<EditorPlayerStopSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        };
    };
};

#endif /* EditorPlayerStopSystem_h */
