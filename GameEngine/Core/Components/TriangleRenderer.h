//
//  TriangleRenderer.h
//  GameEngine
//
//  Created by Felippe Durán on 14/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef TriangleRenderer_h
#define TriangleRenderer_h

#include <glm/glm.hpp>
#include "Program.h"

struct TriangleRenderer {
public:
    TriangleRenderer(tdogl::Program *program) : program(program) {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &vertVBO);
        glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
        
        vertexData = new glm::vec3[3];
        vertexData[0] = glm::vec3(-1.0f, 1.0f, 0.0f);
        vertexData[1] = glm::vec3(-1.0f, -1.0f, 0.0f);
        vertexData[2] = glm::vec3(1.0f, -1.0f, 0.0f);
        
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec3), vertexData, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(program->attrib("vert"));
        glVertexAttribPointer(program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
        
        glGenBuffers(1, &colorVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
        
        colorData = new glm::vec4[3];
        colorData[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        colorData[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        colorData[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
        
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), colorData, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(program->attrib("vertColor"));
        glVertexAttribPointer(program->attrib("vertColor"), 4, GL_FLOAT, GL_TRUE, sizeof(glm::vec4), NULL);
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    
    ~TriangleRenderer() {
        delete[] vertexData;
        delete[] colorData;
    }
    
    GLuint VAO;
    tdogl::Program *program;
    
private:
    GLuint vertVBO;
    GLuint colorVBO;
    
    glm::vec3 *vertexData;
    glm::vec4 *colorData;
};

#endif /* TriangleRenderer_h */
