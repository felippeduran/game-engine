//
//  Velocity2d.h
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef Velocity2d_h
#define Velocity2d_h

#include <glm/glm.hpp>

namespace GameEngine {
    namespace Editor {
        struct Velocity2d {
            Velocity2d() : Velocity2d(glm::vec3()) {};
            Velocity2d(glm::vec3 velocity) : velocity(velocity) {};
            glm::vec2 velocity;
        };
    };
};

#endif /* Velocity2d_h */
