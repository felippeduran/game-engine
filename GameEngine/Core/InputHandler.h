//
//  InputHandler.h
//  GameEngine
//
//  Created by Felippe Durán on 26/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef InputHandler_h
#define InputHandler_h

class GLFWwindow;

class InputHandler {
public:
    void errorCallback(int error, const char* description);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    void cursorEnterCallback(GLFWwindow* window, int entered);
};

#endif /* InputHandler_h */
