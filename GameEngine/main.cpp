//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include "EngineObjectPool.h"
#include "ShaderManager.h"

using namespace std;

static EngineGLFWInitializer initializer;
static EngineObjectPool objectPool;
static ShaderManager shaderManager;

int main(int argc, const char * argv[]) {
    
    
    int error = 0;
    error = initializer.initialize();
    if (!error) {
        shaderManager.createProgram("colorShader", "vertex_shader.glsl", "fragment_shader.glsl");
        
        error = initializer.runLoop(bind(&EngineObjectPool::update, &objectPool, placeholders::_1));
    }
    
    return error;
}
