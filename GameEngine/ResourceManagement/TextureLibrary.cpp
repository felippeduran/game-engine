//
//  TextureLibrary.cpp
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "TextureLibrary.h"
#include "Texture.h"
#include "platform.hpp"

using namespace std;
using namespace tdogl;

Texture *TextureLibrary::getTexture(string filename) {
    Texture *texture = nullptr;
    if (textures.find(filename) != textures.end()) texture = textures[filename];
    else {
        Bitmap bmp = Bitmap::bitmapFromFile(ResourcePath(filename));
        bmp.flipVertically();
        texture = new Texture(bmp);
        textures[filename] = texture;
    }
    return texture;
}
