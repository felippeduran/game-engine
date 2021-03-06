//
//  MenuSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 08/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef MenuSystem_h
#define MenuSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct MenuSystem : public entityx::System<MenuSystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
            
        private:
            void showMenuFile();
            void showToggledPlay();
        };
    };
};

#endif /* MenuSystem_h */
