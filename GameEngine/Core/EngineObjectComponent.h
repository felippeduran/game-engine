//
//  EngineObjectComponent.h
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineObjectComponent_h
#define EngineObjectComponent_h

#include <vector>

class EngineObject;
class EngineObjectTransform;
class EngineObjectPool;

class EngineObjectComponent {
public:
    EngineObjectComponent(EngineObject *object, EngineObjectPool *objectPool) : object(object), objectPool(objectPool) {};
    virtual ~EngineObjectComponent() {};
    
    EngineObject *getObject() const;
    EngineObjectPool *getObjectPool() const;
    EngineObjectTransform *getTransform() const;
    
    virtual void update(double dt) = 0;
    
    virtual void onUnregistered() {};
    virtual void onRegistered() {};
    
    void registerComponent();
    void unregisterComponent();
    
    void destroy();
    
protected:
    EngineObject *object;
    EngineObjectPool *objectPool;
};

#endif /* EngineObjectComponent_h */
