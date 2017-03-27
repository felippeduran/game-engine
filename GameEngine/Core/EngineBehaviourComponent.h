//
//  EngineBehaviourComponent.h
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineBehaviourComponent_h
#define EngineBehaviourComponent_h

#include "EngineObjectComponent.h"

class EngineBehaviourComponent : public EngineObjectComponent {
public:
    EngineBehaviourComponent(object_id objectId, EngineObjectPool *objectPool) : EngineObjectComponent(objectId, objectPool) {};
    
    void setEnabled(bool enabled);
    bool isEnabled() const;
    
    virtual void onEnable();
    virtual void onDisable();
    
    void onUnregistered() override final;
    void onRegistered() override final;
    
private:
    bool enabled;
    
    using EngineObjectComponent::registerComponent;
    using EngineObjectComponent::unregisterComponent;
};

#endif /* EngineObjectBehaviour_h */
