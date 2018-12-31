//
//  InputHandler.cpp
//  GameEngine
//
//  Created by Felippe Durán on 26/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "InputHandler.h"
#include <GLFW/glfw3.h>
#include "Engine.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "MouseEnter.h"
#include "MousePositionEvent.h"
#include "MouseScrollPositionEvent.h"

using namespace glm;
using namespace entityx;
using namespace GameEngine;

void InputHandler::resetOrder() {
    order = 0;
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
//    fprintf(stdout, "Key: %d, action: %d\n", key, action);
    Entity entity = engine->entities.create();
    entity.assign<KeyboardInput>(order++, key, action);
}

void InputHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
//    fprintf(stdout, "Mouse pos: (%.2f, %.2f)\n", xpos, ypos);
    Entity entity = engine->entities.create();
    entity.assign<MousePositionEvent>(order++, vec2(xpos, ypos));
}

void InputHandler::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
//    fprintf(stdout, "Mouse button: %d, action: %d\n", button, action);
    Entity entity = engine->entities.create();
    entity.assign<MouseInput>(order++, button, action);
}

void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    //    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
//    fprintf(stdout, "Scroll: (%.2f, %.2f)\n", xoffset, yoffset);
    Entity entity = engine->entities.create();
    entity.assign<MouseScrollPositionEvent>(order++, vec2(xoffset, yoffset));
}

void InputHandler::cursorEnterCallback(GLFWwindow* window, int entered) {
//    fprintf(stdout, "Cursor entered: %d\n", entered);
    Entity entity = engine->entities.create();
    entity.assign<MouseEnter>(entered);
}
