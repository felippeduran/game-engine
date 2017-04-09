//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include "EngineLoop.h"
#include "ShaderManager.h"

using namespace std;

static EngineGLFWInitializer initializer;
static EngineLoop engineLoop;
static ShaderManager shaderManager;

int main(int argc, const char * argv[]) {
    
    
    int error = 0;
    error = initializer.initialize();
    if (!error) {
        shaderManager.createProgram("colorShader", "vertex_shader.glsl", "fragment_shader.glsl");
        
        error = initializer.runLoop(bind(&EngineLoop::update, &engineLoop, placeholders::_1));
    }
    
    return error;
}
