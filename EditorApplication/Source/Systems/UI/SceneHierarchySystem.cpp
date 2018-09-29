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
#include "EntitySorter.h"

using namespace entityx;
using namespace glm;
using namespace std;

void SceneHierarchySystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<SceneHierarchy>([this, &es, &events, dt] (Entity entity, SceneHierarchy &menu) {
        if (ImGui::Begin("Scene Hierarchy", NULL, 0))
        {
            static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
            int node_clicked = -1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
            
            showChildNodes(es.entities_with_components<Transform, Name>(), Entity::INVALID, selection_mask, node_clicked);
            
            if (node_clicked != -1)
            {
                // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            
            ImGui::End();
        }
    });
};

void SceneHierarchySystem::showChildNodes(EntityManager::View<Transform, Name> view, Entity::Id parentId, int& selection_mask, int& node_clicked)
{
    int i = 0;
    view.each([this, &view, &parentId, &selection_mask, &node_clicked, &i] (Entity entity, Transform &transform, Name &name) {
        if (entity.component<Transform>()->parent.id() == parentId) {
            ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0);
            
            int children = countChildNodes(view, entity.id());
            if (!children) node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "%s", entity.component<Name>()->name.c_str());
            if (ImGui::IsItemClicked()) node_clicked = i;
            if (children && node_open) {
                showChildNodes(view, entity.id(), selection_mask, node_clicked);
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
