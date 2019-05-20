//
//  SpotLight.h
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef SpotLight_h
#define SpotLight_h

#include <glm/glm.hpp>

namespace GameEngine {
    struct SpotLight {
        SpotLight() : SpotLight(glm::vec3(1.0f, 1.0f, 1.0f), 0.14f, 0.07f, 12.5f) {};
        SpotLight(glm::vec3 color, float linearAttenuation, float quadraticAttenuation, float cutOff) : color(color), linearAttenuation(linearAttenuation), quadraticAttenuation(quadraticAttenuation), cutOff(cutOff) {};
        
        glm::vec3 color;
        float linearAttenuation;
        float quadraticAttenuation;
        float cutOff;
    };
};

#endif /* SpotLight_h */
