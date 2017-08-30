//
//  Mesh.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Mesh.h"

using namespace glm;

Mesh::Mesh(int vertexCount, vec3 *vertices, int *triangles, vec4 *colors, vec3 *normals, vec2 *uv) : vertexCount(vertexCount), vertices(vertices), triangles(triangles), colors(colors), normals(normals), uv(uv) {
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vec3), vertices, GL_STATIC_DRAW);
    
    if (colors) {
        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vec4), colors, GL_STATIC_DRAW);
    }
    
    if (normals) {
        glGenBuffers(1, &normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vec3), normals, GL_STATIC_DRAW);
    }
    
    if (uv) {
        glGenBuffers(1, &uvVBO);
        glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
        
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vec2), uv, GL_STATIC_DRAW);
    }
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertexVBO);
    if (colors) glDeleteBuffers(1, &colorVBO);
    if (normals) glDeleteBuffers(1, &normalVBO);
    if (uv) glDeleteBuffers(1, &uvVBO);
}
