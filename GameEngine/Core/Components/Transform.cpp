//
//  Transform.cpp
//  GameEngine
//
//  Created by Felippe Durán on 25/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

using namespace glm;

void Transform::setTransform(const mat4& modelMatrix) {
    vec3 skew;
    vec4 perspective;
    decompose(modelMatrix, localScale, localRotation, localPosition, skew, perspective);
}
