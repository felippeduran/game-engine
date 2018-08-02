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
#include "tdogl/Program.h"
#include "tdogl/Texture.h"

struct Material {
    Material(tdogl::Program* program, tdogl::Texture* texture = nullptr) : program(program), texture(texture) {};
    tdogl::Program* program;
    tdogl::Texture* texture;
};

#endif /* Material_h */
