//
//  main.cpp
//  GameDemo
//
//  Created by Felippe Durán on 16/12/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include <iostream>

#include "Engine.h"
#include <entityx/deps/Dependencies.h>

#include "InputHandler.h"
#include "EngineGLFWInitializer.h"

#include "Name.h"
#include "Transform.h"
#include "TransformSystem.h"
#include "Camera.h"
#include "CameraSystem.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Material.h"
#include "DirectionalLight.h"

#include "ShaderManager.h"
#include "Program.h"

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "MaterialLibrary.h"
#include "MeshLibrary.h"

using namespace std;
using namespace entityx;
using namespace GameEngine;

extern "C" int initialize(Engine *engine);

int main(int argc, const char * argv[]) {
    InputHandler *inputHandler = new InputHandler();
    EngineGLFWInitializer *initializer = new EngineGLFWInitializer();
    
    int error = 0;
    error = initializer->initialize(inputHandler);
    
    Engine *engine = new Engine(inputHandler);
    engine->initialize();
    engine->configure();
    initialize(engine);
    if (!error) error = initializer->runLoop(bind(&Engine::update, engine, placeholders::_1));
    
    delete engine;
    delete initializer;
    delete inputHandler;
    
    return error;
}

int initialize(Engine *engine) {
    Entity cameraEntity = engine->entities.create();
    cameraEntity.assign<Name>("Camera");
    cameraEntity.assign<Camera>();
    cameraEntity.component<Transform>()->localPosition = glm::vec3(10.0f, 0.0f, 10.0f);
    cameraEntity.component<Transform>()->localRotation = glm::quat(glm::radians(glm::vec3(20, 45, 0)));
    
    Entity parentEntity = engine->entities.create();
    
    parentEntity.assign<Transform>();
    parentEntity.assign<Name>("Root");

    Entity lightEntity = engine->entities.create();
    lightEntity.assign<Name>("Light");
    lightEntity.assign<DirectionalLight>();
    lightEntity.component<Transform>()->localPosition = glm::vec3(0.0f, 15.0f, -20.0f);
    lightEntity.component<DirectionalLight>()->ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    lightEntity.component<DirectionalLight>()->diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    lightEntity.component<DirectionalLight>()->specular = glm::vec3(1.0f, 1.0f, 1.0f);
    lightEntity.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
//    lightEntity.component<MeshRenderer>()->mesh->materials[0]->colorDiffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    lightEntity.component<Transform>()->localScale = glm::vec3(0.01f, 0.01f, 0.01f);
    lightEntity.component<Transform>()->localRotation = glm::quat(glm::radians(glm::vec3(180, 90, 0)));
    
    Entity entity = engine->entities.create();
    entity.assign<MeshRenderer>(engine->meshLibrary->loadMesh("link.obj"));
    
    entity.component<Transform>()->parent = parentEntity;
    entity.component<Transform>()->localRotation = glm::quat(glm::vec3(0.0f, 0.0f, M_PI/4.0f));
    entity.component<Transform>()->localScale = glm::vec3(0.1f, 0.1f, 0.1f);
    entity.component<Transform>()->localPosition = glm::vec3(0, -10, -10);
    entity.assign<Name>("Link");
    
//    Entity entityChild3 = engine->entities.create();
//    entityChild3.assign<Transform>();
//    entityChild3.assign<Name>("CameraChild");
//    entityChild3.component<Transform>()->parent = cameraEntity;
    
    Entity cubeEntity = engine->entities.create();
    cubeEntity.assign<Name>("Cube");
    cubeEntity.assign<MeshRenderer>(engine->meshLibrary->loadMesh("cube.obj"));
    
//    Entity entity2 = engine->entities.create();
//    entity2.assign<Name>("LinkRef");
//    entity2.assign<MeshRenderer>(engine->meshLibrary->loadMesh("link.obj"));
//    entity2.component<Transform>()->localScale = glm::vec3(0.1f, 0.1f, 0.1f);
    //    entity2.component<Transform>()->localScale = glm::vec3(1.0f, 1.0f, 0.001f);
    
//    Entity entity3 = engine->entities.create();
//    entity3.assign<MeshRenderer>(engine->meshLibrary->loadMesh("axes.obj"));
//    //    entity3.component<Transform>()->localScale = glm::vec3(0.01f, 0.01f, 0.01f);
//    entity3.assign<Name>("LinkRef2");
//    entity3.component<Transform>()->parent = entity;
    
//    Entity entity4 = engine->entities.create();
//    entity4.assign<MeshRenderer>(engine->meshLibrary->loadMesh("axes.obj"));
//    //    entity4.component<Transform>()->localScale = glm::vec3(0.01f, 0.01f, 0.01f);
//    entity4.component<Transform>()->localPosition = glm::vec3(65, 75, 0);
//    entity4.component<Transform>()->localRotation = glm::quat(glm::vec3(0.0f, 0.0f, -M_PI/4.0f));
//    entity4.assign<Name>("LinkRef3");
//    entity4.component<Transform>()->parent = entity;
    
    Entity entityChild0 = engine->entities.create();
    entityChild0.assign<Transform>();
    entityChild0.assign<Name>("LinkChildChildChild");
    
    Entity entityChild1 = engine->entities.create();
    entityChild1.assign<Transform>();
    entityChild1.assign<Name>("LinkChildChild");
    
    Entity entityChild2 = engine->entities.create();
    entityChild2.assign<Transform>();
    entityChild2.assign<Name>("LinkChild");
    
    entityChild2.component<Transform>()->parent = entity;
    entityChild1.component<Transform>()->parent = entityChild2;
    entityChild0.component<Transform>()->parent = entityChild1;
    
    return 0;
}
