//
//  TextureLibrary.h
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef TextureLibrary_h
#define TextureLibrary_h

#include <stdio.h>
#include <unordered_map>

namespace tdogl {
    class Texture;
}

class TextureLibrary {
public:
    tdogl::Texture *getTexture(std::string texture);
    
private:
    std::unordered_map<std::string, tdogl::Texture *> textures;
};

#endif /* TextureLibrary_h */
