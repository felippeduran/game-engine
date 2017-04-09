//
//  EngineObjectComponent.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineObjectComponent.h"
#include "EngineObject.h"
#include "EngineLoop.h"

EngineObject *EngineObjectComponent::getObject() const {
    return engineLoop->getObject(objectId);
}

EngineLoop *EngineObjectComponent::getEngineLoop() const {
    return engineLoop;
}

EngineTransformComponent *EngineObjectComponent::getTransform() const {
    return getObject()->getTransform();
}

void EngineObjectComponent::registerComponent() {
    std::cout << "EngineObjectComponent register component!" << std::endl;
    engineLoop->registerComponent(this);
}

void EngineObjectComponent::unregisterComponent() {
    std::cout << "EngineObjectComponent unregister component!" << std::endl;
    engineLoop->unregisterComponent(this);
}

void EngineObjectComponent::destroy() {
    engineLoop->destroyComponent(this);
}
