//
//  KeyboardInputSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 11/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef KeyboardInputSystem_h
#define KeyboardInputSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

struct KeyboardInputSystem : public entityx::System<KeyboardInputSystem> {
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    
private:
    std::vector<int> keysIds;
};

#endif /* KeyboardInputSystem_h */
