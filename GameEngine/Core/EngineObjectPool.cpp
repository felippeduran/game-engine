//
//  EngineObjectPool.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineObjectPool.h"
#include "EngineObject.h"
#include "EngineObjectComponent.h"

object_id EngineObjectPool::createObject() {
    object_id id = objects.createObject();
    getObject(id)->setObjectPool(this);
    registerObject(id);
    return id;
}

EngineObject* EngineObjectPool::getObject(object_id id) {
    return objects.getObject(id);
}

void EngineObjectPool::destroyObject(object_id id) {
    destroyedObjects.insert(id);
}

void EngineObjectPool::registerObject(object_id id) {
    if (registeredObjects.find(id) == registeredObjects.end()) registeringObjects.insert(id);
}

void EngineObjectPool::unregisterObject(object_id id) {
    if (registeredObjects.find(id) != registeredObjects.end()) unregisteringObjects.insert(id);
}

void EngineObjectPool::destroyComponent(EngineObjectComponent *component) {
    destroyedComponents.insert(component);
}

void EngineObjectPool::registerComponent(EngineObjectComponent *component) {
    if (registeredComponents.find(component) == registeredComponents.end()) registeringComponents.insert(component);
}

void EngineObjectPool::unregisterComponent(EngineObjectComponent *component) {
    if (registeredComponents.find(component) != registeredComponents.end()) unregisteringComponents.insert(component);
}

void EngineObjectPool::update(double dt) {
    std::cout << "EngineObjectPool update!" << " dt: " << dt << std::endl;
    registerObjects();
    registerComponents();
    
    updateTransforms();
    updateRegisteredComponents(dt);
    
    unregisterObjects();
    unregisterComponents();
    
    std::cout << "EngineObjectPool destruction phase!" << " dt: " << dt << std::endl;
    cleanupDestroyedObjects();
    cleanupDestroyedComponents();
    destroyObjects();
    destroyComponents();
    
    std::cout << std::endl << std::endl;
}

void EngineObjectPool::unregisterObjects() {
    std::cout << "EngineObjectPool unregister " << unregisteringObjects.size() << " objects!" << std::endl;
    for (object_id id : unregisteringObjects) {
        getObject(id)->onUnregistered();
    }
    
    registeredObjects.erase(unregisteringObjects.begin(), unregisteringObjects.end());
    unregisteringObjects.clear();
}

void EngineObjectPool::registerObjects() {
    std::cout << "EngineObjectPool register " << registeringObjects.size() << " objects!" << std::endl;
    for (object_id id : registeringObjects) {
        getObject(id)->onRegistered();
    }
    
    registeredObjects.insert(registeringObjects.begin(), registeringObjects.end());
    registeringObjects.clear();
}

void EngineObjectPool::unregisterComponents() {
    std::cout << "EngineObjectPool unregister " << unregisteringComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : unregisteringComponents) {
        component->onUnregistered();
        registeredComponents.erase(component);
    }
    unregisteringComponents.clear();
}

void EngineObjectPool::registerComponents() {
    std::cout << "EngineObjectPool register " << registeringComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : registeringComponents) {
        component->onRegistered();
    }
    
    registeredComponents.insert(registeringComponents.begin(), registeringComponents.end());
    registeringComponents.clear();
}


void EngineObjectPool::updateRegisteredComponents(double dt) {
    std::cout << "EngineObjectPool update " << registeredComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : registeredComponents) {
        component->update(dt);
    }
}

void EngineObjectPool::updateTransforms() {
    std::cout << "EngineObjectPool update " << registeredObjects.size() << " transforms!" << std::endl;
    for (object_id id : registeredObjects) {
        objects.getObject(id)->getTransform();
    }
}

void EngineObjectPool::cleanupDestroyedObjects() {
    std::cout << "EngineObjectPool cleanup " << destroyedObjects.size() << " destroyed objects!" << std::endl;
    for (object_id id : destroyedObjects) {
        EngineObject *object = getObject(id);
        for (EngineObjectComponent *component : object->getComponents<EngineObjectComponent>()) {
            destroyComponent(component);
        }
        registeredObjects.erase(id);
    }
}

void EngineObjectPool::cleanupDestroyedComponents() {
    std::cout << "EngineObjectPool cleanup " << destroyedObjects.size() << " destroyed components!" << std::endl;
    for (EngineObjectComponent *component : destroyedComponents) {
        unregisterComponent(component);
    }
    unregisterComponents();
}

void EngineObjectPool::destroyObjects() {
    std::cout << "EngineObjectPool purge " << destroyedObjects.size() << " objects!" << std::endl;
    for (object_id id : destroyedObjects) {
        objects.destroyObject(id);
    }
    destroyedObjects.clear();
}

void EngineObjectPool::destroyComponents() {
    std::cout << "EngineObjectPool purge " << destroyedComponents.size() << " components!" << std::endl;
    for (EngineObjectComponent *component : destroyedComponents) {
        delete component;
    }
    destroyedComponents.clear();
}
