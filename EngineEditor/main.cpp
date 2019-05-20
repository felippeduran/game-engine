//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "Engine.h"
#include <entityx/deps/Dependencies.h>

#include "InputHandler.h"
#include "EngineGLFWInitializer.h"

#include "Name.h"
#include "Transform.h"
#include "Camera.h"
#include "EditorCamera.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "VelocitySystem.h"
#include "MouseMovementSystem.h"
#include "EditorCameraRotationSystem.h"
#include "KeyboardMovementSystem.h"
#include "EditorCameraRotationEnableSystem.h"

#include "EditorPlayerStopSystem.h"
#include "EditorPlayerStartSystem.h"
#include "EditorPlayerUpdateSystem.h"

#include "MenuSystem.h"
#include "Menu.h"

#include "InspectorSystem.h"
#include "Inspector.h"

#include "SceneHierarchySystem.h"
#include "SceneHierarchy.h"

#include "Velocity.h"
#include "Movable.h"
#include "Rotatable.h"
#include "Position2d.h"
#include "Velocity2d.h"
#include "Mouse.h"
#include "SceneElement.h"
#include "EditorElement.h"

#include "Project.h"

#include <dlfcn.h>

#include "MeshRenderer.h"
#include "MeshLibrary.h"

using namespace std;
using namespace entityx;
using namespace GameEngine;
using namespace GameEngine::Editor;

void setupScene(Engine *engine);

int main(int argc, const char * argv[]) {
    InputHandler *inputHandler = new InputHandler();
    EngineGLFWInitializer *initializer = new EngineGLFWInitializer();
    
    int error = 0;
    error = initializer->initialize(inputHandler);
    
    Engine *engine = new Engine(inputHandler);
    engine->initialize();
    
    engine->systems.add<MouseMovementSystem>();
    engine->systems.add<KeyboardMovementSystem>();
    engine->systems.add<EditorCameraRotationEnableSystem>();
    engine->systems.add<EditorCameraRotationSystem>();
    engine->systems.add<VelocitySystem>();
    
    engine->systems.add<MenuSystem>();
    engine->systems.add<SceneHierarchySystem>();
    engine->systems.add<InspectorSystem>();
    
    engine->systems.add<EditorPlayerStopSystem>();
    engine->systems.add<EditorPlayerStartSystem>(inputHandler);
    engine->systems.add<EditorPlayerUpdateSystem>();
    
    engine->systems.add<deps::Dependency<Velocity, Transform>>();
    engine->systems.add<deps::Dependency<Movable, Velocity>>();
    engine->systems.add<deps::Dependency<Rotatable, Transform>>();
    engine->systems.add<deps::Dependency<EditorCamera, Camera>>();
    engine->systems.add<deps::Dependency<Velocity2d, Position2d>>();
    engine->systems.add<deps::Dependency<Mouse, Velocity2d>>();
    
    engine->configure();

    setupScene(engine);
    if (!error) error = initializer->runLoop(bind(&Engine::update, engine, placeholders::_1));
    engine->cleanup();
    
    delete engine;
    delete initializer;
    delete inputHandler;
    
    return error;
}

void setupScene(Engine *engine) {
    Entity lightEntity = engine->entities.create();
    lightEntity.assign<Name>("Light");
    lightEntity.assign<SceneElement>();
    lightEntity.assign<PointLight>();
//    lightEntity.assign<Transform>();
    lightEntity.assign<AmbientLight>(glm::vec3(0.1f, 0.1f, 0.1f));
    lightEntity.component<Transform>()->localScale = glm::vec3(0.2f, 0.2f, 0.2f);
    lightEntity.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    
    Entity lightEntity2 = engine->entities.create();
    lightEntity2.assign<Name>("SpotLight");
    lightEntity2.assign<SceneElement>();
    lightEntity2.assign<SpotLight>();
    lightEntity2.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    lightEntity2.component<Transform>()->localScale = glm::vec3(0.2f, 0.2f, 0.2f);
    lightEntity2.component<Transform>()->localPosition = glm::vec3(5.0f, 5.0f, -5.0f);
    lightEntity2.component<Transform>()->localRotation = glm::quat(glm::radians(glm::vec3(-150, -45, 0)));
    
    
    Entity menuEntity = engine->entities.create();
    menuEntity.assign<Menu>();
    
    Entity sceneHierarchyEntity = engine->entities.create();
    sceneHierarchyEntity.assign<SceneHierarchy>();
    
    Entity inspectorEntity = engine->entities.create();
    inspectorEntity.assign<Inspector>();
    
    Entity mouseEntity = engine->entities.create();
    mouseEntity.assign<Name>("Mouse");
    mouseEntity.assign<Mouse>();

    Entity cameraEntity = engine->entities.create();
    cameraEntity.assign<Name>("EditorCamera");
    cameraEntity.assign<EditorCamera>();
    cameraEntity.assign<Movable>();
    cameraEntity.component<Transform>()->localPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    cameraEntity.component<Velocity>()->speed = 10.0f;
    
    
    Entity cubeEntity = engine->entities.create();
    cubeEntity.assign<Name>("Cube");
    cubeEntity.assign<SceneElement>();
    cubeEntity.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    cubeEntity.component<Transform>()->localPosition = glm::vec3(0.0f, 2.0f, 0.0f);
    cubeEntity.component<Transform>()->localRotation = glm::quat(glm::radians(glm::vec3(45, 45, 0)));
    
    Entity cubeEntity2 = engine->entities.create();
    cubeEntity2.assign<Name>("Cube");
    cubeEntity2.assign<SceneElement>();
    cubeEntity2.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    cubeEntity2.component<Transform>()->localPosition = glm::vec3(2.0f, 0.0f, 0.0f);
    
    Entity cubeEntity3 = engine->entities.create();
    cubeEntity3.assign<Name>("Cube");
    cubeEntity3.assign<SceneElement>();
    cubeEntity3.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    cubeEntity3.component<Transform>()->localPosition = glm::vec3(-2.0f, 0.0f, 0.0f);
    
    
    typedef int (*game_initialize)(Engine *engine);
    
    void *sharedObject = dlopen("./libGameDemoLib.dylib", RTLD_NOW);
    printf("%s\n", dlerror());
    dlerror();
    
    Entity projectEntity = engine->entities.create();
    projectEntity.assign<Project>("GameDemo", sharedObject);
}
