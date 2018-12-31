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

using namespace std;
using namespace tdogl;
using namespace tinyobj;
using namespace GameEngine;

Material *MaterialLibrary::getMaterial(material_t& materialData) {
    vector<Texture *> textures;
    vector<TextureType> textureTypes;
    if (!materialData.diffuse_texname.empty()) {
        textures.push_back(textureLibrary->getTexture(materialData.diffuse_texname));
        textureTypes.push_back(TextureType::Diffuse);
    }
    if (!materialData.specular_texname.empty()) {
        textures[TextureType::Specular] = textureLibrary->getTexture(materialData.specular_texname);
        textureTypes.push_back(TextureType::Specular);
    }
    if (!materialData.bump_texname.empty()) {
        textures[TextureType::Normal] = textureLibrary->getTexture(materialData.bump_texname);
        textureTypes.push_back(TextureType::Normal);
    }
    Program *program = shaderManager->getProgram("basic_program");
    Material *material = new Material(materialData, program, textures, textureTypes);
    return material;
}
