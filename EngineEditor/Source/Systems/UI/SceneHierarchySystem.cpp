//
//  SceneHierarchySystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 08/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "SceneHierarchySystem.h"
#include "SceneHierarchy.h"
#include "imgui.h"
#include "Transform.h"
#include "Name.h"
#include "InspectorHighlight.h"

using namespace entityx;
using namespace glm;
using namespace std;
using namespace GameEngine;
using namespace GameEngine::Editor;

void SceneHierarchySystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<SceneHierarchy>([this, &es, &events, dt] (Entity entity, SceneHierarchy &menu) {
        if (ImGui::Begin("Scene Hierarchy", NULL, 0)) {
            Entity node_clicked;
            showChildNodes(es.entities_with_components<Transform, Name>(), Entity::INVALID, node_clicked);
            if (node_clicked.valid()) {
                if (ImGui::GetIO().KeyCtrl) {
                    if (node_clicked.has_component<InspectorHighlight>()) node_clicked.remove<InspectorHighlight>();
                    else node_clicked.assign<InspectorHighlight>();
                } else {
                    es.each<InspectorHighlight>([this, &es, &events, dt] (Entity entity, InspectorHighlight &highlight) {
                        entity.remove<InspectorHighlight>();
                    });
                    node_clicked.assign<InspectorHighlight>();
                }
            }
        }
        ImGui::End();
    });
};

void SceneHierarchySystem::showChildNodes(EntityManager::View<Transform, Name> view, Entity::Id parentId, Entity& node_clicked)
{
    int i = 0;
    view.each([this, &view, &parentId, &node_clicked, &i] (Entity entity, Transform &transform, Name &name) {
        if (entity.component<Transform>()->parent.id() == parentId) {
            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | entity.has_component<InspectorHighlight>();
            
            int children = countChildNodes(view, entity.id());
            if (!children) node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            bool node_open = ImGui::TreeNodeEx((void*)entity.id().id(), node_flags, "%s", entity.component<Name>()->name.c_str());
            if (ImGui::IsItemClicked()) node_clicked = entity;
            if (children && node_open) {
                showChildNodes(view, entity.id(), node_clicked);
                ImGui::TreePop();
            }
        }
        i++;
    });
}

int SceneHierarchySystem::countChildNodes(EntityManager::View<Transform, Name> view, Entity::Id parentId)
{
    int children = 0;
    view.each([this, &view, &parentId, &children] (Entity entity, Transform &transform, Name &name) {
        if (entity.component<Transform>()->parent.id() == parentId) children++;
    });
    
    return children;
}
