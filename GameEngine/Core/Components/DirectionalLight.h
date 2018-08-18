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

struct DirectionalLight {
    DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {};
    
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};  

#endif /* DirectionalLight_h */
