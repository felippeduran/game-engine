//
//  Mesh.h
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Mesh_h
#define Mesh_h

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <tiny_obj_loader.h>
#include "Submesh.h"

namespace GameEngine {
    class Material;

    class Mesh {
    public:
        std::vector<glm::vec3> combinedVertices;
        std::vector<glm::vec3> combinedNormals;
        std::vector<glm::vec2> combinedTexCoords;
        std::vector<int> combinedIndices;
        std::vector<Submesh> submeshes;
        std::vector<Material *> materials;
        
        GLuint vertexVBO = 0;
        GLuint uvVBO = 0;
        GLuint normalVBO = 0;
        GLuint IBO = 0;
        std::vector<GLuint> shapeVAOs;
        
        Mesh(std::vector<glm::vec3> combinedVertices, std::vector<glm::vec3> combinedNormals, std::vector<glm::vec2> combinedTexCoords, std::vector<int> combinedIndices, std::vector<Submesh> submeshes, std::vector<Material *> materials);
        ~Mesh();
    };
};

#endif /* Mesh_h */
