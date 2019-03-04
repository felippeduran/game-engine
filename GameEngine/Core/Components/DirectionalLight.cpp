//
//  DirectionalLight.cpp
//  GameEngine
//
//  Created by Felippe Durán on 23/02/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "DirectionalLight.h"
#include "MetadataType.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    DirectionalLight *component(Entity entity) {
        return entity.component<DirectionalLight>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<DirectionalLight>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<DirectionalLight>("Directional Light")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Ambient Color", &DirectionalLight::ambient)
    .property("Diffuse Color", &DirectionalLight::diffuse)
    .property("Specular Color", &DirectionalLight::specular)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}
