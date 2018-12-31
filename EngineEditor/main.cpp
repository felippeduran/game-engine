//
//  main.cpp
//  GameEngine
//
//  Created by Felippe Durán on 2/3/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "GameEngine.h"
#include <entityx/deps/Dependencies.h>

#include "Name.h"
#include "Transform.h"
#include "Camera.h"
#include "EditorCamera.h"
#include "DirectionalLight.h"

#include "VelocitySystem.h"
#include "MouseMovementSystem.h"
#include "EditorCameraRotationSystem.h"
#include "KeyboardMovementSystem.h"
#include "EditorCameraRotationEnableSystem.h"

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

using namespace std;
using namespace entityx;

GameEngine engine;

void setupScene();

int main(int argc, const char * argv[]) {
    int error = engine.initialize();
    
    engine.systems.add<MouseMovementSystem>();
    engine.systems.add<KeyboardMovementSystem>();
    engine.systems.add<EditorCameraRotationEnableSystem>();
    engine.systems.add<EditorCameraRotationSystem>();
    engine.systems.add<VelocitySystem>();
    
    engine.systems.add<MenuSystem>();
    engine.systems.add<SceneHierarchySystem>();
    engine.systems.add<InspectorSystem>();
    
    engine.systems.add<deps::Dependency<Velocity, Transform>>();
    engine.systems.add<deps::Dependency<Movable, Velocity>>();
    engine.systems.add<deps::Dependency<Rotatable, Transform>>();
    engine.systems.add<deps::Dependency<EditorCamera, Camera>>();
    engine.systems.add<deps::Dependency<Velocity2d, Position2d>>();
    engine.systems.add<deps::Dependency<Mouse, Velocity2d>>();
    
    engine.configure();

    setupScene();
    if (!error) error = engine.start();
    return error;
}

void setupScene() {
    Entity lightEntity = engine.entities.create();
    lightEntity.assign<Name>("Light");
    lightEntity.assign<DirectionalLight>();
    lightEntity.component<Transform>()->localPosition = glm::vec3(0.0f, 15.0f, -20.0f);
    
    
    Entity menuEntity = engine.entities.create();
    menuEntity.assign<Menu>();
    
    Entity sceneHierarchyEntity = engine.entities.create();
    sceneHierarchyEntity.assign<SceneHierarchy>();
    
    Entity inspectorEntity = engine.entities.create();
    inspectorEntity.assign<Inspector>();
    
    Entity parentEntity = engine.entities.create();
    parentEntity.assign<Transform>();
    parentEntity.assign<Name>("Root");

    Entity mouseEntity = engine.entities.create();
    mouseEntity.assign<Name>("Mouse");
    mouseEntity.assign<Mouse>();

    Entity cameraEntity = engine.entities.create();
    cameraEntity.assign<Name>("EditorCamera");
    cameraEntity.assign<EditorCamera>();
    cameraEntity.assign<Movable>();
    cameraEntity.component<Transform>()->localPosition = glm::vec3(0.0f, 0.0f, 5.0f);
    cameraEntity.component<Velocity>()->speed = 10.0f;
}
