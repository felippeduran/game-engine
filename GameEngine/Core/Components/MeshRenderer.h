//
//  MeshRenderer.h
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef MeshRenderer_h
#define MeshRenderer_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <entityx.h>

namespace GameEngine {
    class Mesh;
    struct Material;

    struct MeshRenderer {
        MeshRenderer() : MeshRenderer(nullptr) {};
        MeshRenderer(Mesh *mesh) : mesh(mesh) {};
        Mesh *mesh;
    };
};

#endif /* MeshRenderer_h */
