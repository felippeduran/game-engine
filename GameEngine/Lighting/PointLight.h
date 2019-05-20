//
//  PointLight.h
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef PointLight_h
#define PointLight_h

#include <glm/glm.hpp>

namespace GameEngine {
    struct PointLight {
        PointLight() : PointLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.14f, 0.07f) {};
        PointLight(glm::vec3 color, float linearAttenuation, float quadraticAttenuation) : color(color), linearAttenuation(linearAttenuation), quadraticAttenuation(quadraticAttenuation) {};
        
        glm::vec3 color;
        float linearAttenuation;
        float quadraticAttenuation;
    };
};

#endif /* PointLight_h */
