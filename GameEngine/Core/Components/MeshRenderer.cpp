//
//  MeshRenderer.cpp
//  GameEngine
//
//  Created by Felippe Durán on 24/02/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "MeshRenderer.h"
#include "MetadataType.h"
#include "Mesh.h"
#include <entityx.h>
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;
using namespace entityx;

namespace {
    MeshRenderer *component(Entity entity) {
        return entity.component<MeshRenderer>().get();
    }
    
    bool has_component(Entity entity) {
        return entity.has_component<MeshRenderer>();
    }
}

RTTR_REGISTRATION
{
    registration::class_<MeshRenderer>("Mesh Renderer")(
        metadata(MetadataType::Component, true)
    )
    .constructor<>()
    .property("Mesh", &MeshRenderer::mesh)
    .method("retrieveComponent", &component)
    .method("hasComponent", &has_component);
}

