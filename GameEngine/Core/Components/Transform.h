//
//  Transform.h
//  GameEngine
//
//  Created by Felippe Durán on 13/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#include <entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform {
    Transform() : localScale(glm::vec3(1.0f, 1.0f, 1.0f)), parent(entityx::Entity()) {};
    
    void setTransform(const glm::mat4& modelMatrix);
    
    glm::vec3 localPosition;
    glm::vec3 localScale;
    glm::quat localRotation;
    glm::mat4 localToWorldMatrix;
    entityx::Entity parent;
};


#endif /* Transform_h */
