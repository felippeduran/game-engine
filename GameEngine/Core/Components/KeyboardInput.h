//
//  KeyboardInput.h
//  GameEngine
//
//  Created by Felippe Durán on 04/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef KeyboardInput_h
#define KeyboardInput_h

struct KeyboardInput {
    KeyboardInput(int order, int key, int state) : order(order), key(key), state(state) {};
    
    int order;
    int key;
    int state;
};

#endif /* KeyboardInput_h */
