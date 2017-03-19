//
//  EngineBehaviourComponent.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineBehaviourComponent.h"
#include "EngineObjectPool.h"

void EngineBehaviourComponent::setEnabled(bool enabled) {
    if (this->enabled != enabled) {
        this->enabled = enabled;
        std::cout << "EngineObjectBehaviour set enabled to " << enabled << "!" << std::endl;
        if (enabled) objectPool->registerComponent(this);
        else objectPool->unregisterComponent(this);
    }
}

bool EngineBehaviourComponent::isEnabled() const {
    return enabled;
}

void EngineBehaviourComponent::onEnable() {
    std::cout << "EngineObjectBehaviour onEnable!" << std::endl;
}

void EngineBehaviourComponent::onDisable() {
    std::cout << "EngineObjectBehaviour onDisable!" << std::endl;
}

void EngineBehaviourComponent::onUnregistered() {
    onDisable();
}

void EngineBehaviourComponent::onRegistered() {
    onEnable();
}
