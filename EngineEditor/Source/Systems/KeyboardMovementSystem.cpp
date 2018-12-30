//
//  KeyboardMovementSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "KeyboardMovementSystem.h"
#include "Transform.h"
#include "KeyboardInput.h"
#include "Velocity.h"
#include "Movable.h"
#include <GLFW/glfw3.h>

using namespace std;
using namespace entityx;
using namespace glm;

void KeyboardMovementSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    const EntityManager::View<KeyboardInput>& entities = es.entities_with_components<KeyboardInput>();
    vector<Entity> sorted;
    sorted.reserve(std::distance(entities.begin(), entities.end()));
    for (Entity entity : entities) {
        sorted.push_back(entity);
    }
    sort(sorted.begin(), sorted.end(), [] (Entity& a, Entity& b) {
        return a.component<KeyboardInput>()->order < b.component<KeyboardInput>()->order;
    });
    
    
    es.each<Transform, Velocity, Movable>([this, &es, &events, &sorted] (Entity entity, Transform &transform, Velocity &velocity, Movable &movable) {
        vec3 vel;
        
        for (Entity entity : sorted) {
            KeyboardInput& keyInput = *entity.component<KeyboardInput>();
            if (keyInput.state == GLFW_PRESS) {
                if (keyInput.key == GLFW_KEY_W) vel -= vec3(0, 0, 1);
                if (keyInput.key == GLFW_KEY_S) vel += vec3(0, 0, 1);
                if (keyInput.key == GLFW_KEY_A) vel -= vec3(1, 0, 0);
                if (keyInput.key == GLFW_KEY_D) vel += vec3(1, 0, 0);
            }
            
            if (keyInput.state == GLFW_RELEASE) {
                if (keyInput.key == GLFW_KEY_W) vel += vec3(0, 0, 1);
                if (keyInput.key == GLFW_KEY_S) vel -= vec3(0, 0, 1);
                if (keyInput.key == GLFW_KEY_A) vel += vec3(1, 0, 0);
                if (keyInput.key == GLFW_KEY_D) vel -= vec3(1, 0, 0);
            }
        }
        
        velocity.direction += vel;
    });
};
