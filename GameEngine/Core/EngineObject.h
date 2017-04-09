//
//  EngineObject.h
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineObject_h
#define EngineObject_h

#include <stddef.h>
#include <vector>

#include "EngineObjectComponent.h"

class EngineTransformComponent;
class EngineLoop;
template <typename T> class slot_map;

class EngineObject {
public:
    EngineTransformComponent *getTransform() const;
    
    object_id getId() const;
    
    void setActive(bool active);
    bool isActive() const;
    
    template <class T> T *addComponent();
    template <class T> T *getComponent() const;
    template <class T> std::vector<T *> getComponents() const;
    
    void destroy();
    
private:
    object_id id;
    bool active;
    EngineLoop *engineLoop;
    EngineTransformComponent *transform;
    std::vector<EngineObjectComponent *> components;
    
    void * operator new   (size_t size) { return ::operator new(size); };
    void * operator new[] (size_t size) { return ::operator new[](size); };
    void   operator delete   (void *p) { return ::operator delete(p); };
    void   operator delete[] (void *p) { return ::operator delete(p); };
    
    void setEngineLoop(EngineLoop *engineLoop);
    
    void insertComponent(EngineObjectComponent *component);
    void removeComponent(EngineObjectComponent *component);
    void onRegistered() const;
    void onUnregistered() const;
    
    friend class slot_map<EngineObject>;
    friend class EngineLoop;
};


#include "EngineLoop.h"

template <class T> T *EngineObject::addComponent() {
    static_assert(std::is_base_of<EngineObjectComponent, T>::value, "Template class is not a EngineObjectComponent!");
    return engineLoop->addComponent<T>(this);
};

template <class T> T *EngineObject::getComponent() const {
    for (const EngineObjectComponent *component : components) {
        T *ptr = dynamic_cast<T*>(component);
        if (ptr) return ptr;
    }
    return nullptr;
};

template <class T> std::vector<T *> EngineObject::getComponents() const {
    std::vector<T *> selected = std::vector<T *>();
    selected.reserve(components.size());
    for (EngineObjectComponent *component : components) {
        T *ptr = dynamic_cast<T*>(component);
        if (ptr) selected.push_back(ptr);
    }
    return selected;
};

#endif /* EngineObject_h */
