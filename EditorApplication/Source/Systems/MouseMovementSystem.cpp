//
//  MouseMovementSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "MouseMovementSystem.h"
#include "MousePositionEvent.h"
#include "Position2d.h"
#include "Velocity2d.h"
#include "Mouse.h"

using namespace std;
using namespace entityx;
using namespace glm;

void MouseMovementSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    
    const EntityManager::View<MousePositionEvent>& entities = es.entities_with_components<MousePositionEvent>();
    vector<Entity> sorted;
    sorted.reserve(std::distance(entities.begin(), entities.end()));
    for (Entity entity : entities) {
        sorted.push_back(entity);
    }
    sort(sorted.begin(), sorted.end(), [] (Entity& a, Entity& b) {
        return a.component<MousePositionEvent>()->order < b.component<MousePositionEvent>()->order;
    });
    
    es.each<Position2d, Velocity2d, Mouse>([this, &es, &events, dt, &sorted] (Entity entity, Position2d &position, Velocity2d &velocity, Mouse& mouse) {
        velocity.velocity = vec2();
        
        for (Entity inputEntity : sorted) {
            MousePositionEvent &mousePositionInput = *inputEntity.component<MousePositionEvent>();
            velocity.velocity = (mousePositionInput.position - position.position);
            position.position = mousePositionInput.position;
        }
    });
};
