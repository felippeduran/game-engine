//
//  GameEngine.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "GameEngine.h"
#include "EngineGLFWInitializer.h"
#include "InputHandler.h"

#include <entityx/deps/Dependencies.h>
#include "Transform.h"
#include "TransformSystem.h"
#include "Camera.h"
#include "CameraSystem.h"
#include "MeshRenderer.h"

#include "ShaderManager.h"
#include "Program.h"

#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "MeshLibrary.h"

using namespace entityx;
using namespace std;

GameEngine::GameEngine() {
    systems.add<deps::Dependency<MeshRenderer, Transform>>();
    systems.add<deps::Dependency<Camera, Transform>>();
    systems.add<CameraSystem>();
    systems.add<TransformSystem>();
    
    systems.configure();
}

int GameEngine::initialize() {
    inputHandler = new InputHandler();
    initializer = new EngineGLFWInitializer();
    
    int error = 0;
    error = initializer->initialize(inputHandler);
    
    systems.add<deps::Dependency<MeshRenderer, Transform>>();
    systems.add<deps::Dependency<Camera, Transform>>();
    systems.add<CameraSystem>();
    systems.add<TransformSystem>();
    
    systems.configure();
    
    shaderManager = new ShaderManager();
    
    shaderManager->createProgram("basic_program", "vertex_shader.glsl", "fragment_shader.glsl");
    
    textureLibrary = new TextureLibrary();
    materialLibrary = new MaterialLibrary(shaderManager, textureLibrary);
    meshLibrary = new MeshLibrary(materialLibrary);
    
    return error;
}

int GameEngine::start() {
    return initializer->runLoop(bind(&GameEngine::update, this, placeholders::_1));
}

GameEngine::~GameEngine() {
    delete inputHandler;
    delete initializer;
    delete shaderManager;
    delete textureLibrary;
    delete materialLibrary;
    delete meshLibrary;
}

void GameEngine::update(TimeDelta dt) {
    systems.update_all(dt);
}
