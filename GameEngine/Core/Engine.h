//
//  Engine.h
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include <entityx.h>

namespace GameEngine {
    class EngineGLFWInitializer;
    class ShaderManager;
    class TextureLibrary;
    class MaterialLibrary;
    class MeshLibrary;
    class InputHandler;
    
    class Engine : public entityx::EntityX {
    public:
        explicit Engine();
        ~Engine();
        
        int initialize();
        void configure();
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
};

#endif /* Engine_h */
