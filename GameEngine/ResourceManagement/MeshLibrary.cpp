//
//  MeshLibrary.cpp
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "MeshLibrary.h"
#include <tiny_obj_loader.h>
#include "Mesh.h"

void loadMesh(const std::string& filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string err;
    tinyobj::LoadObj(&attrib, &shapes, &materials, &err, filename.c_str());
    
    if (!err.empty()) { // `err` may contain warning message.
        std::cerr << err << std::endl;
    }
}
