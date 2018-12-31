//
//  Engine.cpp
//  GameEngine
//
//  Created by Felippe Durán on 12/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Engine.h"
#include "EngineGLFWInitializer.h"
#include "InputHandler.h"

#include <entityx/deps/Dependencies.h>
#include "TransformSystem.h"
#include "CameraSystem.h"
#include "InputCleanupSystem.h"

#include "Transform.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"

#include "ShaderManager.h"
#include "Program.h"

#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "MeshLibrary.h"

using namespace entityx;
using namespace std;
using namespace GameEngine;

Engine::Engine() {
    systems.add<InputCleanupSystem>();
}

int Engine::initialize() {
    inputHandler = new InputHandler(this);
    initializer = new EngineGLFWInitializer();
    
    int error = 0;
    error = initializer->initialize(inputHandler);
    
    systems.add<deps::Dependency<MeshRenderer, Transform>>();
    systems.add<deps::Dependency<Camera, Transform>>();
    systems.add<deps::Dependency<DirectionalLight, Transform>>();
    systems.add<CameraSystem>();
    systems.add<TransformSystem>();
    
    shaderManager = new ShaderManager();
    
    shaderManager->createProgram("basic_program", "vertex_shader.glsl", "fragment_shader.glsl");
    
    textureLibrary = new TextureLibrary();
    materialLibrary = new MaterialLibrary(shaderManager, textureLibrary);
    meshLibrary = new MeshLibrary(materialLibrary);
    
    return error;
}

void Engine::configure() {
    systems.configure();
}

int Engine::start() {
    return initializer->runLoop(bind(&Engine::update, this, placeholders::_1));
}

Engine::~Engine() {
    delete inputHandler;
    delete initializer;
    delete shaderManager;
    delete textureLibrary;
    delete materialLibrary;
    delete meshLibrary;
}

void Engine::update(TimeDelta dt) {
    systems.update_all(dt);
}
