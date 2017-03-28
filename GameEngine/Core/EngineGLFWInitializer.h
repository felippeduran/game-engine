//
//  EngineGLFWInitializer.h
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineGLFWInitializer_h
#define EngineGLFWInitializer_h

#include <functional>

class GLFWwindow;

class EngineGLFWInitializer {
public:
    int initialize();
    int runLoop(std::function<void (float dt)> updateCallback);
    
private:
    GLFWwindow *window;
};

#endif /* EngineGLFWInitializer_h */
