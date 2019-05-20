//
//  SpotLight.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "SpotLight.h"
#include "MetadataType.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    SpotLight *component(Entity entity) {
        return entity.component<SpotLight>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<SpotLight>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<SpotLight>("Spot Light")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Color", &SpotLight::color)
    .property("Linear Attenuation", &SpotLight::linearAttenuation)
    .property("Quadratic Attenuation", &SpotLight::quadraticAttenuation)
    .property("Cutoff", &SpotLight::cutOff)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
