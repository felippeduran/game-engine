//
//  EngineLoop.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineLoop.h"
#include "EngineObject.h"
#include "EngineObjectComponent.h"

#include "EngineTransformComponent.h"

object_id EngineLoop::createObject() {
    object_id id = objects.createObject();
    getObject(id)->setEngineLoop(this);
    return id;
}

EngineObject* EngineLoop::getObject(object_id id) {
    return objects.getObject(id);
}

void EngineLoop::destroyObject(object_id id) {
    destroyedObjects.insert(id);
}

void EngineLoop::destroyComponent(EngineObjectComponent *component) {
    destroyedComponents.insert(component);
}

void EngineLoop::registerComponent(EngineObjectComponent *component) {
    if (registeredComponents.find(component) == registeredComponents.end()) registeringComponents.insert(component);
}

void EngineLoop::unregisterComponent(EngineObjectComponent *component) {
    if (registeredComponents.find(component) != registeredComponents.end()) unregisteringComponents.insert(component);
}

void EngineLoop::update(double dt) {
    std::cout << "EngineLoop update!" << " dt: " << dt << std::endl;
    registerComponents();
    
    updateRegisteredComponents(dt);
    
    unregisterComponents();
    
    std::cout << "EngineLoop destruction phase!" << " dt: " << dt << std::endl;
    cleanupDestroyedObjects();
    cleanupDestroyedComponents();
    destroyObjects();
    destroyComponents();
    
    std::cout << std::endl << std::endl;
}

void EngineLoop::unregisterComponents() {
    std::cout << "EngineLoop unregister " << unregisteringComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : unregisteringComponents) {
        component->onUnregistered();
        registeredComponents.erase(component);
    }
    unregisteringComponents.clear();
}

void EngineLoop::registerComponents() {
    std::cout << "EngineLoop register " << registeringComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : registeringComponents) {
        component->onRegistered();
    }
    
    registeredComponents.insert(registeringComponents.begin(), registeringComponents.end());
    registeringComponents.clear();
}


void EngineLoop::updateRegisteredComponents(double dt) {
    std::cout << "EngineLoop update " << registeredComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : registeredComponents) {
        component->update(dt);
    }
}

void EngineLoop::cleanupDestroyedObjects() {
    std::cout << "EngineLoop cleanup " << destroyedObjects.size() << " destroyed objects!" << std::endl;
    for (object_id id : destroyedObjects) {
        EngineObject *object = getObject(id);
        for (EngineObjectComponent *component : object->getComponents<EngineObjectComponent>()) {
            destroyComponent(component);
        }
    }
}

void EngineLoop::cleanupDestroyedComponents() {
    std::cout << "EngineLoop cleanup " << destroyedComponents.size() << " destroyed components!" << std::endl;
    for (EngineObjectComponent *component : destroyedComponents) {
        unregisterComponent(component);
    }
    unregisterComponents();
}

void EngineLoop::destroyObjects() {
    std::cout << "EngineLoop purge " << destroyedObjects.size() << " objects!" << std::endl;
    for (object_id id : destroyedObjects) {
        objects.destroyObject(id);
    }
    destroyedObjects.clear();
}

void EngineLoop::destroyComponents() {
    std::cout << "EngineLoop purge " << destroyedComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : destroyedComponents) {
        delete component;
    }
    destroyedComponents.clear();
}
