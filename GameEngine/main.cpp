//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include "ShaderManager.h"
#include "Application.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    EngineGLFWInitializer initializer;
    
    int error = 0;
    error = initializer.initialize();
    if (!error) {
        Application application;
        error = initializer.runLoop(bind(&Application::update, &application, placeholders::_1));
    }
    
    return error;
}
