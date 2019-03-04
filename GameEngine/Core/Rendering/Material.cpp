//
//  Material.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Material.h"
#include "MetadataType.h"
#include <rttr/registration>

using namespace GameEngine;
using namespace rttr;

RTTR_REGISTRATION
{
    registration::class_<Material>("Material")
    .constructor<>()
    .property("Name", &Material::name)
    .property("Ambient Color", &Material::colorAmbient)
    .property("Diffuse Color", &Material::colorDiffuse)
    .property("Specular Color", &Material::colorSpecular)
    .property("Dissolve", &Material::dissolve)
    .property("Refraction Index", &Material::refractionIndex)
    .property("Specular Exponent", &Material::specularExponent);
}

