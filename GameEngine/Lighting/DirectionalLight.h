//
//  DirectionalLight.h
//  GameEngine
//
//  Created by Felippe Durán on 11/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef DirectionalLight_h
#define DirectionalLight_h

#include <glm/glm.hpp>

//class Card {
//public:
//    string name = "Felipe Gaspar Durán";
//    string email = "felippe.duran@gmail.com";
//    string twitter-github-linkedin = "@felippeduran";
//}

namespace GameEngine {
    struct DirectionalLight {
        DirectionalLight() : DirectionalLight(glm::vec3(1.0f, 1.0f, 1.0f)) {};
        DirectionalLight(glm::vec3 color) : color(color) {};
        
        glm::vec3 color;
    };
};

#endif /* DirectionalLight_h */
