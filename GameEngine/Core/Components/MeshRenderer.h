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

struct Mesh;
struct Material;

struct MeshRenderer {
    MeshRenderer(const entityx::ComponentHandle<Mesh>& mesh, Material *material);
    ~MeshRenderer();
    
    entityx::ComponentHandle<Mesh> mesh;
    Material *material;
    GLuint vao;
};

#endif /* MeshRenderer_h */
