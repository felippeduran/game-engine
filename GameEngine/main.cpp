//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include "EngineObjectPool.h"

using namespace std;

static EngineGLFWInitializer initializer;
static EngineObjectPool objectPool;

int main(int argc, const char * argv[]) {
    
    initializer.initialize(bind(&EngineObjectPool::update, &objectPool, placeholders::_1));
    
    return 0;
}
