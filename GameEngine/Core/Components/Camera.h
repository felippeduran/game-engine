//
//  Camera.h
//  GameEngine
//
//  Created by Felippe Durán on 18/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include <glm/gtx/transform.hpp>

struct Camera {
    Camera(float fieldOfView = glm::radians(50.0f), float aspect = 800.0f/600.0f, float zNear = 0.1f, float zFar = 10.0f) : projection(glm::perspective(fieldOfView, aspect, zNear, zFar)) {};
    
    glm::mat4 projection;
};

#endif /* Camera_h */
