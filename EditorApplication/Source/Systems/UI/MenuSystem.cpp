//
//  MenuSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 08/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "MenuSystem.h"
#include "Menu.h"
#include "imgui.h"

using namespace entityx;
using namespace glm;

void MenuSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Menu>([this, &es, &events, dt] (Entity entity, Menu &menu) {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ShowMenuFile();
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
            ImGui::EndMainMenuBar();
        }
    });
};

void MenuSystem::ShowMenuFile() {
    ImGui::MenuItem("(dummy menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
}
