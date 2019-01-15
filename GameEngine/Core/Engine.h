//
//  Engine.h
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include "EngineInterface.h"
#include <entityx.h>

namespace GameEngine {
    class ShaderManager;
    class TextureLibrary;
    class MaterialLibrary;
    class MeshLibrary;
    class InputHandler;
    
    class Engine : public entityx::EntityX, public EngineInterface {
    public:
        explicit Engine(InputHandler *inputHandler);
        ~Engine();
        
        void initialize() override;
        void configure() override;
        void cleanup() override;
        
        entityx::Entity create() override;
        
        void update(entityx::TimeDelta dt) override;
        
        ShaderManager *shaderManager;
        TextureLibrary *textureLibrary;
        MaterialLibrary *materialLibrary;
        MeshLibrary *meshLibrary;
        InputHandler *inputHandler;
    };
};

#endif /* Engine_h */
