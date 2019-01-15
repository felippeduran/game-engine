//
//  EditorPlayerStartSystem.h
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef EditorPlayerStartSystem_h
#define EditorPlayerStartSystem_h

#include <entityx.h>

namespace GameEngine {
    class InputHandler;
    
    namespace Editor {
        struct EditorPlayerStartSystem : public entityx::System<EditorPlayerStartSystem> {
            EditorPlayerStartSystem(InputHandler *inputHandler) : inputHandler(inputHandler) {};
            
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
            
        private:
            InputHandler *inputHandler;
        };
    };
};

#endif /* EditorPlayerStartSystem_h */
