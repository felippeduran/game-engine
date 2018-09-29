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
#include "TransformSystem.h"
#include "Camera.h"
#include "EditorCamera.h"
#include "CameraSystem.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"

#include "ShaderManager.h"
#include "Program.h"

#include <glm/glm.hpp>

#include "MaterialLibrary.h"
#include "MeshLibrary.h"

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
    
    int error = engine.initialize();
    setupScene();
    if (!error) error = engine.start();
    return error;
}

void setupScene() {
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
    cameraEntity.component<Velocity>()->speed = 10.0f;
}
