//
//  EngineGLFWInitializer.cpp
//  GameEngine
//
//  Created by Felippe Durán on 3/13/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "EngineGLFWInitializer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "InputHandler.h"

using namespace std;

static InputHandler *inputHandler = nullptr;

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void cursorEnterCallback(GLFWwindow* window, int entered);

int EngineGLFWInitializer::initialize(InputHandler *inputHandler) {
    inputHandler = inputHandler;
    
    glfwSetErrorCallback(errorCallback);

    glfwInit();
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    window = glfwCreateWindow(800, 600, "GameEngine", nullptr, nullptr);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if (!window) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetCursorEnterCallback(window, cursorEnterCallback);
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW." << std::endl;
        return -1;
    }
    
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    
    glfwSwapInterval(1);
    
    glViewport(0, 0, screenWidth, screenHeight);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    return 0;
}

int EngineGLFWInitializer::runLoop(function<void (float)> updateCallback) {
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        double time = glfwGetTime();
        updateCallback(time - lastTime);
        lastTime = time;
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    inputHandler->keyCallback(window, key, scancode, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    inputHandler->cursorPosCallback(window, xpos,ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    inputHandler->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    inputHandler->scrollCallback(window, xoffset, yoffset);
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
    inputHandler->cursorEnterCallback(window, entered);
}
