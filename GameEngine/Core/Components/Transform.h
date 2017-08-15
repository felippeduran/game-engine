//
//  Transform.h
//  GameEngine
//
//  Created by Felippe Durán on 13/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Transform_h
#define Transform_h

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

struct Position {
    Position(glm::vec3 localPosition = glm::vec3()) : localPosition(localPosition) {};
    
    glm::vec3 localPosition;
};

struct Rotation {
    Rotation(glm::quat localRotation = glm::quat()) : localRotation(localRotation) {};
    
    glm::quat localRotation;
};

struct Scale {
    Scale(glm::vec3 localScale = glm::vec3()) : localScale(localScale) {};
    
    glm::vec3 localScale;
};

struct Parent {
    Parent(entityx::Entity parent = entityx::Entity()) : parent(parent) {};
    
    entityx::Entity parent;
};

struct Transform {
    glm::mat4 modelMatrix;
    glm::mat4 localToWorldMatrix;
};


#endif /* Transform_h */
