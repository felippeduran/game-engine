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

struct Material {
    Material(tinyobj::material_t& materialData, tdogl::Program* program, tdogl::Texture* texture = nullptr) :
        colorAmbient(glm::vec3(materialData.ambient[0], materialData.ambient[1], materialData.ambient[2])),
        colorDiffuse(glm::vec3(materialData.diffuse[0], materialData.diffuse[1], materialData.diffuse[2])),
        colorSpecular(glm::vec3(materialData.specular[0], materialData.specular[1], materialData.specular[2])),
        program(program),
        texture(texture) {};
    
    tdogl::Program* program;
    tdogl::Texture* texture;
    glm::vec3 colorAmbient; // Ka
    glm::vec3 colorDiffuse; // Kd
    glm::vec3 colorSpecular; // Ks
    float specularExponent; // Ns
    float refractionIndex; // Ni
    float transparency; // d
    int illuminationModel; // illum
};

#endif /* Material_h */
