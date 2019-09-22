//
//  MaterialLibrary.h
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef MaterialLibrary_h
#define MaterialLibrary_h

#include <stdio.h>
#include <tiny_obj_loader.h>

namespace GameEngine {
    class Material;
    class ShaderManager;
    class TextureLibrary;

    class MaterialLibrary {
    public:
        MaterialLibrary(ShaderManager *shaderManager, TextureLibrary *textureLibrary) : shaderManager(shaderManager), textureLibrary(textureLibrary) {};
        
        Material *getMaterial(tinyobj::material_t& material, std::string basedir);
        
    private:
        ShaderManager *shaderManager;
        TextureLibrary *textureLibrary;
    };
};

#endif /* MaterialLibrary_h */
