//
//  EngineObjectPool.h
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineObjectPool_h
#define EngineObjectPool_h

#include <set>
#include <vector>
#include "slot_map.h"

class EngineObject;
class EngineObjectComponent;

class EngineObjectPool {
public:    
    void update(double dt);
    
    object_id createObject();
    EngineObject* getObject(object_id id);
    void destroyObject(object_id id);
    
    void registerObject(object_id id);
    void unregisterObject(object_id id);
    
    template <class T> T *addComponent(EngineObject *object);
    void destroyComponent(EngineObjectComponent *component);
    
    void registerComponent(EngineObjectComponent *component);
    void unregisterComponent(EngineObjectComponent *component);
    
private:
    std::set<object_id> registeredObjects;
    std::set<object_id> registeringObjects;
    std::set<object_id> unregisteringObjects;
    std::set<object_id> destroyedObjects;
    slot_map<EngineObject> objects;
    
    std::set<EngineObjectComponent *> registeredComponents;
    std::set<EngineObjectComponent *> registeringComponents;
    std::set<EngineObjectComponent *> unregisteringComponents;
    std::set<EngineObjectComponent *> destroyedComponents;
    
    void registerObjects();
    void unregisterObjects();
    void unregisterComponents();
    void registerComponents();
    
    void updateRegisteredComponents(double dt);
    void updateTransforms();
    void cleanupDestroyedObjects();
    void cleanupDestroyedComponents();
    void destroyObjects();
    void destroyComponents();
};


#include "EngineObject.h"

template <class T> T* EngineObjectPool::addComponent(EngineObject *object) {
    static_assert(std::is_base_of<EngineObjectComponent, T>::value, "Template class is not a EngineObjectComponent!");
    T *component = new T(object, this);
    object->insertComponent(component);
    return component;
}

#endif /* EngineObjectPool_h */
