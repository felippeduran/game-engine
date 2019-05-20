//
//  AmbientLight.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "AmbientLight.h"
#include "MetadataType.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    AmbientLight *component(Entity entity) {
        return entity.component<AmbientLight>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<AmbientLight>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<AmbientLight>("Ambient Light")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Color", &AmbientLight::color)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
