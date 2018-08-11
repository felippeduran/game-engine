//
//  MaterialLibrary.cpp
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "MaterialLibrary.h"
#include "Material.h"
#include "TextureLibrary.h"
#include "ShaderManager.h"

using namespace tdogl;
using namespace tinyobj;

Material *MaterialLibrary::getMaterial(material_t materialData) {
    Texture *texture = nullptr;
    if (!materialData.diffuse_texname.empty()) texture = textureLibrary->getTexture(materialData.diffuse_texname);
    Program *program = shaderManager->getProgram("basic_program");
    Material *material = new Material(materialData, program, texture);
    return material;
}
