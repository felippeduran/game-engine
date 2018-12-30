//
//  main.cpp
//  GameDemo
//
//  Created by Felippe Durán on 16/12/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include <iostream>
#include "GameEngine.h"

using namespace std;
using namespace entityx;

extern "C" int initialize(GameEngine& engine);

int main(int argc, const char * argv[]) {
    GameEngine engine;
    int error = engine.initialize();
    engine.configure();
    initialize(engine);
    if (!error) error = engine.start();
    return error;
}

int initialize(GameEngine& engine) {
    return 0;
}
