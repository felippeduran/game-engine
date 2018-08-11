//
//  KeyboardKeyState.h
//  GameEngine
//
//  Created by Felippe Durán on 11/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef KeyboardKeyState_h
#define KeyboardKeyState_h

struct KeyboardKeyState {
    KeyboardKeyState(int key, int state) : key(key), state(state) {};
    
    int key;
    int state;
};

#endif /* KeyboardKeyState_h */
