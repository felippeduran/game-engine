//
//  Program.cpp
//  GameEngine
//
//  Created by Felippe Durán on 15/05/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Program.h"
#include <OpenGL/gl3.h>
#include <iostream>
#include <vector>

using namespace std;

Program::Program(GLuint vertShader, GLuint fragShader) : _program(0), _vertShader(vertShader), _fragShader(fragShader) {
    
    int link_result = 0;
    //create the program handle, attatch the shaders and link it
    _program = glCreateProgram();
    if (!_program) throw std::runtime_error("glCreateProgram failed");
    
    glAttachShader(_program, vertShader);
    glAttachShader(_program, fragShader);
    
    glLinkProgram(_program);
    glGetProgramiv(_program, GL_LINK_STATUS, &link_result);
    //check for link errors
    if (link_result == GL_FALSE) {
        int info_log_length = 0;
        glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &info_log_length);
        vector<char> program_log(info_log_length);
        glGetProgramInfoLog(_program, info_log_length, NULL, &program_log[0]);
        throw std::runtime_error(string("Program linking error:" ) + &program_log[0]);
    }
}

Program::~Program() {
    glDeleteProgram(_program);
}

void Program::use() {
    glUseProgram(_program);
}

GLint Program::getAttribute(const GLchar* attribName) const {
    if(!attribName) throw runtime_error("attribName cannot be NULL");
    
    GLint attrib = glGetAttribLocation(_program, attribName);
    if(attrib == -1) throw runtime_error(string("Program attribute not found: ") + attribName);
    return attrib;
}

GLint Program::getUniform(const GLchar* uniformName) const {
    if(!uniformName) throw runtime_error("uniformName cannot be NULL");
    
    GLint uniform = glGetUniformLocation(_program, uniformName);
    if(uniform == -1) throw runtime_error(string("Program uniform not found: ") + uniformName);
    
    return uniform;
}
