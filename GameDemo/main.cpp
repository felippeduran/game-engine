//
//  main.cpp
//  GameDemo
//
//  Created by Felippe Durán on 16/12/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include <iostream>

#include "Engine.h"

using namespace std;
using namespace entityx;
using namespace GameEngine;

extern "C" int initialize(Engine& engine);

int main(int argc, const char * argv[]) {
    Engine engine;
    int error = engine.initialize();
    engine.configure();
    initialize(engine);
    if (!error) error = engine.start();
    return error;
}

int initialize(Engine& engine) {
    return 0;
}
