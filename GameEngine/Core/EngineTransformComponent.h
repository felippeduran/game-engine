//
//  EngineTransformComponent.h
//  GameEngine
//
//  Created by Felippe Durán on 3/14/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef EngineTransformComponent_h
#define EngineTransformComponent_h

#include "EngineObjectComponent.h"

class EngineTransformComponent : public EngineObjectComponent {
private:
    using EngineObjectComponent::registerComponent;
    using EngineObjectComponent::unregisterComponent;
};

#endif /* EngineTransformComponent_h */
