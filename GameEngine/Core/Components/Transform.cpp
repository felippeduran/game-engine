//
//  Transform.cpp
//  GameEngine
//
//  Created by Felippe Durán on 25/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>
#include <rttr/registration>
#include "MetadataType.h"


using namespace glm;
using namespace GameEngine;
using namespace rttr;

using namespace entityx;

void Transform::setTransform(const mat4& modelMatrix) {
    vec3 skew;
    vec4 perspective;
    decompose(modelMatrix, localScale, localRotation, localPosition, skew, perspective);
}

vec3 Transform::forward() {
    return localToWorldMatrix * vec4(vec3(0.0f, 0.0f, 1.0f), 0.0f);
}

vec3 Transform::right() {
    return localToWorldMatrix * vec4(vec3(1.0f, 0.0f, 0.0f), 0.0f);
}

Transform *component(Entity entity) {
    return entity.component<Transform>().get();
}

bool has_component(Entity entity) {
    return entity.has_component<Transform>();
}

RTTR_REGISTRATION
{
    registration::class_<Transform>("Transform")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Position", &Transform::localPosition)
    .property("Rotation", &Transform::localRotation)
    .property("Scale", &Transform::localScale)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
