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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;

static InputHandler *inputHandlerPtr = nullptr;

void errorCallback(int error, const char* description);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void cursorEnterCallback(GLFWwindow* window, int entered);
void charCallback(GLFWwindow* window, unsigned int c);

int EngineGLFWInitializer::initialize(InputHandler *inputHandler) {
    inputHandlerPtr = inputHandler;
    
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
    glfwSetCharCallback(window, charCallback);
    
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
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    
    ImGui_ImplGlfw_InitForOpenGL(window, false);
    ImGui_ImplOpenGL3_Init("#version 410 core");
    
    // Setup style
    ImGui::StyleColorsDark();
    
    return 0;
}

int EngineGLFWInitializer::runLoop(function<void (float)> updateCallback) {
    double lastTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        double time = glfwGetTime();
        updateCallback(time - lastTime);
        lastTime = time;
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    glfwTerminate();
    return 0;
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    inputHandlerPtr->keyCallback(window, key, scancode, action, mods);
}

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    inputHandlerPtr->cursorPosCallback(window, xpos,ypos);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    inputHandlerPtr->mouseButtonCallback(window, button, action, mods);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    inputHandlerPtr->scrollCallback(window, xoffset, yoffset);
}

void cursorEnterCallback(GLFWwindow* window, int entered) {
    inputHandlerPtr->cursorEnterCallback(window, entered);
}

void charCallback(GLFWwindow* window, unsigned int c) {
    ImGui_ImplGlfw_CharCallback(window, c);
}
