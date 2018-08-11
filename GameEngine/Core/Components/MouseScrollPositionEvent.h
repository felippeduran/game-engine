//
//  MouseScrollPositionEvent.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef MouseScrollPositionEvent_h
#define MouseScrollPositionEvent_h

#include <glm/glm.hpp>

struct MouseScrollPositionEvent {
    MouseScrollPositionEvent(int order, glm::vec2 position) : order(order), position(position) {};
    
    int order;
    glm::vec2 position;
};

#endif /* MouseScrollPositionEvent_h */
