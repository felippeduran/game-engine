//
//  Camera.cpp
//  GameEngine
//
//  Created by Felippe Durán on 18/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Camera.h"
#include "MetadataType.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    Camera *component(Entity entity) {
        return entity.component<Camera>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<Camera>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<Camera>("Camera")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Field Of View", &Camera::fieldOfView)
    .property("Aspect Ratio", &Camera::aspectRatio)
    .property("Near Plane", &Camera::zNear)
    .property("Far Plane", &Camera::zFar)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
