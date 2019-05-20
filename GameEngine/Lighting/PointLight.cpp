//
//  PointLight.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/05/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "PointLight.h"
#include "MetadataType.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    PointLight *component(Entity entity) {
        return entity.component<PointLight>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<PointLight>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<PointLight>("Point Light")(
        metadata(MetadataType::Component, true)
    ).constructor<>()
    .property("Color", &PointLight::color)
    .property("Linear Attenuation", &PointLight::linearAttenuation)
    .property("Quadratic Attenuation", &PointLight::quadraticAttenuation)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
