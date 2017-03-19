//
//  EngineObject.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineObject.h"
#include "EngineObjectPool.h"
#include "EngineObjectComponent.h"

using namespace std;

EngineObjectTransform *EngineObject::getTransform() const {
    return transform;
}

void EngineObject::setActive(bool active) {
    if (this->active != active) {
        this->active = active;
        std::cout << "EngineObject set active to " << active << "!" << std::endl;
        if (active) objectPool->registerObject(id);
        else objectPool->unregisterObject(id);
    }
}

bool EngineObject::isActive() const {
    return active;
}

void EngineObject::setObjectPool(EngineObjectPool *objectPool) {
    this->objectPool = objectPool;
}

void EngineObject::destroy() {
    objectPool->destroyObject(id);
}

void EngineObject::insertComponent(EngineObjectComponent *component) {
    components.push_back(component);
    component->registerComponent();
}

void EngineObject::removeComponent(EngineObjectComponent *component) {
    components.erase(find(components.begin(), components.end(), component));
    component->unregisterComponent();
}

void EngineObject::onRegistered() const {
    std::cout << "EngineObject register components!" << std::endl;
    for (EngineObjectComponent *component : components) {
        component->registerComponent();
    }
}

void EngineObject::onUnregistered() const {
    std::cout << "EngineObject unregister components!" << std::endl;
    for (EngineObjectComponent *component : components) {
        component->unregisterComponent();
    }
}
