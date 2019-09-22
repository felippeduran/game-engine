//
//  Path.cpp
//  GameEngine
//
//  Created by Felippe Durán on 02/09/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "Path.h"
#include <libgen.h>

using namespace std;

string Path::basename()
{
    char path[fullpath.length()];
    strcpy(path, fullpath.c_str());
    return string(::basename(path));
}

string Path::dirname()
{
    char path[fullpath.length()];
    strcpy(path, fullpath.c_str());
    return string(::dirname(path));
}
