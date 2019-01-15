//
//  InputHandler.h
//  GameEngine
//
//  Created by Felippe Durán on 26/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef InputHandler_h
#define InputHandler_h

#include <set>

class GLFWwindow;

namespace GameEngine {
    class EngineInterface;
    
    class InputHandler {
    public:
        InputHandler() : order(0) {};
        
        void addEngine(EngineInterface *engine);
        void removeEngine(EngineInterface *engine);

        void errorCallback(int error, const char* description);
        void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
        void cursorEnterCallback(GLFWwindow* window, int entered);
        
        void resetOrder();
        
    private:
        std::set<EngineInterface *> engines;
        int order;
    };
};

#endif /* InputHandler_h */
