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

struct Mesh {
    Mesh(int vertexCount, glm::vec3 *vertices, int *triangles, glm::vec4 *colors = nullptr, glm::vec3 *normals = nullptr, glm::vec2 *uv = nullptr);
    ~Mesh();
    
    glm::vec3 *vertices;
    glm::vec3 *normals;
    glm::vec4 *colors;
    glm::vec2 *uv;
    int *triangles;
    int vertexCount;
    GLuint vertexVBO = 0;
    GLuint normalVBO = 0;
    GLuint colorVBO = 0;
    GLuint uvVBO = 0;
};

#endif /* Mesh_h */
