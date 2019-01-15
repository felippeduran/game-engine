//
//  Playing.h
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef Playing_h
#define Playing_h

namespace GameEngine {
    class Engine;
    
    namespace Editor {
        struct Playing {
            Playing() : Playing(nullptr) {};
            Playing(Engine *engine) : engine(engine) {};
            
            Engine *engine;
        };
    };
};

#endif /* Playing_h */
