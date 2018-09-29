//
//  SceneHierarchySystem.h
//  GameEngine
//
//  Created by Felippe Durán on 08/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef SceneHierarchySystem_h
#define SceneHierarchySystem_h

#include <entityx.h>
#include <glm/glm.hpp>
#include "Transform.h"
#include "Name.h"

struct SceneHierarchySystem : public entityx::System<SceneHierarchySystem> {
    void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
    
private:
    void showChildNodes(entityx::EntityManager::View<Transform, Name> view, entityx::Entity::Id parentId, int& selection_mask, int& node_clicked);
    int countChildNodes(entityx::EntityManager::View<Transform, Name> view, entityx::Entity::Id parentId);
};

#endif /* SceneHierarchySystem_h */
