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
class EngineTransformComponent;
class EngineLoop;

class EngineObjectComponent {
public:
    EngineObjectComponent(object_id objectId, EngineLoop *engineLoop) : objectId(objectId), engineLoop(engineLoop) {};
    virtual ~EngineObjectComponent() {};
    
    EngineObject *getObject() const;
    EngineLoop *getEngineLoop() const;
    EngineTransformComponent *getTransform() const;
    
    virtual void update(double dt) {};
    
    virtual void onUnregistered() {};
    virtual void onRegistered() {};
    
    void registerComponent();
    void unregisterComponent();
    
    void destroy();
    
protected:
    object_id objectId;
    EngineLoop *engineLoop;
};

#endif /* EngineObjectComponent_h */
