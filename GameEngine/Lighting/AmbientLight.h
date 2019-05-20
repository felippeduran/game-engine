//
//  AmbientLight.h
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef AmbientLight_h
#define AmbientLight_h

#include <glm/glm.hpp>

namespace GameEngine {
    struct AmbientLight {
        AmbientLight() : AmbientLight(glm::vec3()) {};
        AmbientLight(glm::vec3 color) : color(color) {};
        
        glm::vec3 color;
    };
};

#endif /* AmbientLight_h */
