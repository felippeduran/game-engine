//
//  GameEngine.h
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef GameEngine_h
#define GameEngine_h

#include <entityx.h>

class EngineGLFWInitializer;
class ShaderManager;
class TextureLibrary;
class MaterialLibrary;
class MeshLibrary;
class InputHandler;

class GameEngine : public entityx::EntityX {
public:
    explicit GameEngine();
    ~GameEngine();
    
    int initialize();
    int start();
    
    void update(entityx::TimeDelta dt);
    
    ShaderManager *shaderManager;
    TextureLibrary *textureLibrary;
    MaterialLibrary *materialLibrary;
    MeshLibrary *meshLibrary;
    InputHandler *inputHandler;
    
private:
    EngineGLFWInitializer *initializer;
};

#endif /* GameEngine_h */
