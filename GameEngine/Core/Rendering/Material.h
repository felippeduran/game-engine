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
    Material(tdogl::Program* program, glm::vec4 color = glm::vec4(1.0, 1.0, 1.0, 1.0), tdogl::Texture* texture = nullptr) : program(program), color(color), texture(texture) {};
    tdogl::Program* program;
    tdogl::Texture* texture;
    glm::vec4 color;
};

#endif /* Material_h */
