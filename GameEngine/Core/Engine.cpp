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
#include "SpotLight.h"
#include "PointLight.h"

#include "ShaderManager.h"
#include "Program.h"

#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "MeshLibrary.h"

using namespace entityx;
using namespace GameEngine;

Engine::Engine(InputHandler *inputHandler) : inputHandler(inputHandler) {
    systems.add<InputCleanupSystem>();
}

void Engine::initialize() {
    inputHandler->addEngine(this);
    
    systems.add<deps::Dependency<MeshRenderer, Transform>>();
    systems.add<deps::Dependency<Camera, Transform>>();
    systems.add<deps::Dependency<DirectionalLight, Transform>>();
    systems.add<deps::Dependency<SpotLight, Transform>>();
    systems.add<deps::Dependency<PointLight, Transform>>();
    systems.add<CameraSystem>();
    systems.add<TransformSystem>();
    
    shaderManager = new ShaderManager();
    
    shaderManager->createProgram("basic_program", "vertex_shader.glsl", "fragment_shader.glsl");
    
    textureLibrary = new TextureLibrary();
    materialLibrary = new MaterialLibrary(shaderManager, textureLibrary);
    meshLibrary = new MeshLibrary(materialLibrary);
}

void Engine::cleanup() {
    inputHandler->removeEngine(this);
}

void Engine::configure() {
    systems.configure();
}

Entity Engine::create() {
    return entities.create();
}

Engine::~Engine() {
    delete shaderManager;
    delete textureLibrary;
    delete materialLibrary;
    delete meshLibrary;
}

void Engine::update(TimeDelta dt) {
    systems.update_all(dt);
}
