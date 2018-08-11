//
//  MouseMovementSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef MouseMovementSystem_h
#define MouseMovementSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

struct MouseMovementSystem : public entityx::System<MouseMovementSystem> {
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    
private:
    void enableCameraAim(entityx::EntityManager &es);
    void disableCameraAim(entityx::EntityManager &es);
};

#endif /* MouseMovementSystem_h */
