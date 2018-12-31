//
//  MousePositionEvent.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef MousePositionEvent_h
#define MousePositionEvent_h

#include <glm/glm.hpp>

namespace GameEngine {
    struct MousePositionEvent {
        MousePositionEvent(int order, glm::vec2 position) : order(order), position(position) {};
        
        int order;
        glm::vec2 position;
    };
};

#endif /* MousePositionEvent_h */
