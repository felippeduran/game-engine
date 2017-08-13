//
//  Application.h
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Application_h
#define Application_h

#include <entityx.h>

class ShaderManager;

class Application : public entityx::EntityX {
public:
    explicit Application();
    ~Application();
    
    void update(entityx::TimeDelta dt);
    
    ShaderManager *shaderManager;
};

#endif /* Application_h */
