//
//  Mesh.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Mesh.h"
#include "Material.h"
#include "Submesh.h"

using namespace std;
using namespace glm;
using namespace tinyobj;

Mesh::Mesh(vector<vec3> combinedVertices, vector<vec3> combinedNormals, vector<vec2> combinedTexCoords, vector<int> combinedIndices, vector<Submesh> submeshes, vector<Material *> materials) : combinedVertices(combinedVertices), combinedNormals(combinedNormals), combinedTexCoords(combinedTexCoords), combinedIndices(combinedIndices), submeshes(submeshes), materials(materials) {
    glGenBuffers(1, &vertexVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
    
    glBufferData(GL_ARRAY_BUFFER, this->combinedVertices.size() * sizeof(vec3), &this->combinedVertices[0], GL_STATIC_DRAW);
    
    if (!combinedTexCoords.empty()) {
        glGenBuffers(1, &uvVBO);
        glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
        glBufferData(GL_ARRAY_BUFFER, this->combinedTexCoords.size() * sizeof(vec2), &this->combinedTexCoords[0], GL_STATIC_DRAW);
    }
    
    if (!combinedNormals.empty()) {
        glGenBuffers(1, &normalVBO);
        glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
        glBufferData(GL_ARRAY_BUFFER, this->combinedNormals.size() * sizeof(vec3), &this->combinedNormals[0], GL_STATIC_DRAW);
    }
    
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->combinedIndices.size() * sizeof(int), &this->combinedIndices[0] , GL_STATIC_DRAW);
    
    shapeVAOs.reserve(this->submeshes.size());
    for (int i = 0; i < this->submeshes.size(); i++) {
        Submesh& submesh = this->submeshes[i];
        Material *material = materials[submesh.materialId];
        
        GLuint shapeVAO;
        glGenVertexArrays(1, &shapeVAO);
        glBindVertexArray(shapeVAO);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->combinedIndices.size() * sizeof(int), &this->combinedIndices[0] , GL_STATIC_DRAW);
        
        glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
        glEnableVertexAttribArray(material->program->attrib("vert"));
        glVertexAttribPointer(material->program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(vec3), NULL);
        
        if (!combinedNormals.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
            glEnableVertexAttribArray(material->program->attrib("vertNormal"));
            glVertexAttribPointer(material->program->attrib("vertNormal"), 3, GL_FLOAT, GL_TRUE, sizeof(vec3), NULL);
        }
        
        if (!combinedTexCoords.empty()) {
            glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
            glEnableVertexAttribArray(material->program->attrib("vertTexCoord"));
            glVertexAttribPointer(material->program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, sizeof(vec2), NULL);
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        shapeVAOs.push_back(shapeVAO);
    }
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &vertexVBO);
    glDeleteBuffers(1, &uvVBO);
    glDeleteBuffers(1, &normalVBO);
    glDeleteBuffers(1, &IBO);
    
    for (int i = 0; i < shapeVAOs.size(); i++) {
        glDeleteVertexArrays(1, &shapeVAOs[i]);
    }
}
