//
//  InspectorSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "InspectorSystem.h"
#include "Inspector.h"
#include "imgui.h"
#include "InspectorHighlight.h"

using namespace entityx;
using namespace glm;

void InspectorSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Inspector>([this, &es, &events, dt] (Entity entity, Inspector &inspector) {
        if (ImGui::Begin("Inspector", NULL, 0)) {
            es.each<InspectorHighlight>([this, &es, &events, dt] (Entity entity, InspectorHighlight &highlight) {
                
            });
            
            ImGui::End();
        }
    });
};
