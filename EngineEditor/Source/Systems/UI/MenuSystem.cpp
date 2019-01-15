//
//  MenuSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 08/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "MenuSystem.h"
#include "Menu.h"
#include "Play.h"
#include "Stop.h"
#include "Playing.h"
#include "imgui.h"

using namespace entityx;
using namespace glm;
using namespace GameEngine::Editor;

void MenuSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Menu>([this, &es, &events, dt] (Entity entity, Menu &menu) {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                showMenuFile();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
                ImGui::Separator();
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                ImGui::EndMenu();
            }
            
            if (entity.has_component<Playing>()) {
                showToggledPlay();
                if (ImGui::IsItemClicked(0)) entity.assign<Stop>();
            } else if (ImGui::Button("Play")) entity.assign<Play>();
            
            ImGui::EndMainMenuBar();
        }
    });
};

void MenuSystem::showToggledPlay() {
    float b = 1.0f; //  test whatever color you need from imgui_demo.cpp e.g.
    float c = 0.5f; //
    int i = 3;
    
    ImGui::PushID("Play");
    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i/7.0f, b, b));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i/7.0f, b, b));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i/7.0f, c, c));
    ImGui::Button("Play");
    ImGui::PopStyleColor(3);
    ImGui::PopID();
}

void MenuSystem::showMenuFile() {
    ImGui::MenuItem("(dummy menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
}
