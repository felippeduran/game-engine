//
//  EngineInterface.h
//  GameEngine
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef EngineInterface_h
#define EngineInterface_h

#include <entityx.h>

namespace GameEngine {
    class EngineInterface {
    public:
        virtual void initialize() = 0;
        virtual void configure() = 0;
        virtual void cleanup() = 0;
        
        virtual entityx::Entity create() = 0;
        
        virtual void update(entityx::TimeDelta dt) = 0;
    };
};

#endif /* EngineInterface_h */
