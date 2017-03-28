//
//  EngineObjectComponent.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineObjectComponent.h"
#include "EngineObject.h"
#include "EngineObjectPool.h"

EngineObject *EngineObjectComponent::getObject() const {
    return objectPool->getObject(objectId);
}

EngineObjectPool *EngineObjectComponent::getObjectPool() const {
    return objectPool;
}

EngineTransformComponent *EngineObjectComponent::getTransform() const {
    return getObject()->getTransform();
}

void EngineObjectComponent::registerComponent() {
    std::cout << "EngineObjectComponent register component!" << std::endl;
    objectPool->registerComponent(this);
}

void EngineObjectComponent::unregisterComponent() {
    std::cout << "EngineObjectComponent unregister component!" << std::endl;
    objectPool->unregisterComponent(this);
}

void EngineObjectComponent::destroy() {
    objectPool->destroyComponent(this);
}
