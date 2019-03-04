//
//  Material.h
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include <glm/glm.hpp>
#include <tiny_obj_loader.h>
#include "tdogl/Program.h"
#include "tdogl/Texture.h"

namespace GameEngine {
    typedef enum {
        Diffuse = 0,
        Normal = 1,
        Specular = 2,
        Count = 3
    } TextureType;
    
    struct Material {
        Material() {};
        Material(tinyobj::material_t& materialData, tdogl::Program *program, std::vector<tdogl::Texture *>& textures, std::vector<TextureType>& textureTypes) :
        colorAmbient(glm::vec3(materialData.ambient[0], materialData.ambient[1], materialData.ambient[2])),
        colorDiffuse(glm::vec3(materialData.diffuse[0], materialData.diffuse[1], materialData.diffuse[2])),
        colorSpecular(glm::vec3(materialData.specular[0], materialData.specular[1], materialData.specular[2])),
        specularExponent(materialData.shininess),
        refractionIndex(materialData.ior),
        dissolve(materialData.dissolve),
        illuminationModel(materialData.illum),
        name(materialData.name),
        program(program),
        textures(textures),
        textureTypes(textureTypes) {};
        
        std::string name;
        tdogl::Program* program;
        std::vector<tdogl::Texture*> textures;
        std::vector<TextureType> textureTypes;
        glm::vec3 colorAmbient; // Ka
        glm::vec3 colorDiffuse; // Kd
        glm::vec3 colorSpecular; // Ks
        float specularExponent; // Ns
        float refractionIndex; // Ni
        float dissolve; // d
        int illuminationModel; // illum
    };
};

#endif /* Material_h */
