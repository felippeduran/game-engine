//
//  MeshRenderer.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"

using namespace entityx;

MeshRenderer::MeshRenderer(const ComponentHandle<Mesh>& mesh, Material *material) : mesh(mesh), material(material) {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexVBO);
    glEnableVertexAttribArray(material->program->attrib("vert"));
    glVertexAttribPointer(material->program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
    
    if (mesh->colorVBO) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->colorVBO);
        glEnableVertexAttribArray(material->program->attrib("vertColor"));
        glVertexAttribPointer(material->program->attrib("vertColor"), 4, GL_FLOAT, GL_TRUE, sizeof(glm::vec4), NULL);
    }
    
    if (mesh->normalVBO) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->normalVBO);
        glEnableVertexAttribArray(material->program->attrib("vertNormal"));
        glVertexAttribPointer(material->program->attrib("vertNormal"), 3, GL_FLOAT, GL_TRUE, sizeof(glm::vec3), NULL);
    }
    
    if (mesh->uvVBO) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->uvVBO);
        glEnableVertexAttribArray(material->program->attrib("vertTexCoord"));
        glVertexAttribPointer(material->program->attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE, sizeof(glm::vec2), NULL);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

MeshRenderer::~MeshRenderer() {
    glDeleteVertexArrays(1, &vao);
}
