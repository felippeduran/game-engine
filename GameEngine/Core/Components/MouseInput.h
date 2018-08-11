//
//  MouseInput.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef MouseInput_h
#define MouseInput_h

struct MouseInput {
    MouseInput(int order, int key, int state) : order(order), key(key), state(state) {};
    
    int order;
    int key;
    int state;
};

#endif /* MouseInput_h */
