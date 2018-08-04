//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "GameEngine.h"

#include "Transform.h"
#include "TransformSystem.h"
#include "Camera.h"
#include "CameraSystem.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "platform.hpp"

#include "ShaderManager.h"
#include "Program.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MaterialLibrary.h"
#include "MeshLibrary.h"

using namespace std;
using namespace entityx;

GameEngine engine;

void setupScene();

int main(int argc, const char * argv[]) {
    int error = engine.initialize();
    setupScene();
    if (!error) error = engine.start();
    return error;
}

void setupScene() {
    
}
