//
//  InputHandler.cpp
//  GameEngine
//
//  Created by Felippe Durán on 26/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "InputHandler.h"
#include <GLFW/glfw3.h>

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    fprintf(stdout, "Key: %d, action: %d\n", key, action);
}

void InputHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    fprintf(stdout, "Mouse pos: (%.2f, %.2f)\n", xpos, ypos);
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    fprintf(stdout, "Mouse button: %d, action: %d\n", button, action);
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
    fprintf(stdout, "Scroll: (%.2f, %.2f)\n", xoffset, yoffset);
}

void InputHandler::cursorEnterCallback(GLFWwindow* window, int entered) {
    fprintf(stdout, "Cursor entered: %d\n", entered);
}
