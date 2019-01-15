//
//  main.cpp
//  GameDemo
//
//  Created by Felippe Durán on 16/12/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include <iostream>

#include "Engine.h"
#include "InputHandler.h"
#include "EngineGLFWInitializer.h"

using namespace std;
using namespace entityx;
using namespace GameEngine;

extern "C" int initialize(Engine *engine);

int main(int argc, const char * argv[]) {
    InputHandler *inputHandler = new InputHandler();
    EngineGLFWInitializer *initializer = new EngineGLFWInitializer();
    
    int error = 0;
    error = initializer->initialize(inputHandler);
    
    Engine *engine = new Engine(inputHandler);
    engine->initialize();
    engine->configure();
    initialize(engine);
    if (!error) error = initializer->runLoop(bind(&Engine::update, engine, placeholders::_1));
    
    delete engine;
    delete initializer;
    delete inputHandler;
    
    return error;
}

int initialize(Engine *engine) {
    return 0;
}
