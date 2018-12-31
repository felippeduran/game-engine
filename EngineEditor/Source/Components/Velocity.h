//
//  Velocity.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef Velocity_h
#define Velocity_h

#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct Velocity {
            Velocity() : Velocity(0.0f, glm::vec3()) {};
            Velocity(float speed, glm::vec3 direction) : speed(speed), direction(direction) {};
            float speed;
            glm::vec3 direction;
        };
    };
};

#endif /* Velocity_h */
