//
//  ShaderManager.cpp
//  OpenGLTutoria1
//
//  Created by Felippe Durán on 1/23/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "ShaderManager.h"
#include "Program.h"
#include "Shader.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace tdogl;
using namespace GameEngine;

ShaderManager::~ShaderManager() {
    for (auto& programPair : programs) {
        delete programPair.second;
    }
    programs.clear();
}

void ShaderManager::createProgram(const string& programName, const string& vertexShaderFilename, const string& fragmentShaderFilename) {
    Shader vertexShader = Shader::shaderFromFile(vertexShaderFilename, GL_VERTEX_SHADER);
    Shader fragmentShader = Shader::shaderFromFile(fragmentShaderFilename, GL_FRAGMENT_SHADER);
    
    programs[programName] = new Program({ vertexShader, fragmentShader });
}

Program *ShaderManager::getProgram(const string& programName) {
    return programs.at(programName);
}
