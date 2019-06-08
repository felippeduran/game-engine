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
#include "SceneElement.h"

namespace GameEngine {
    namespace Editor {
        struct SceneHierarchySystem : public entityx::System<SceneHierarchySystem> {
            void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
            
        private:
            void showChildNodes(entityx::EntityManager::View<Transform, SceneElement, Name> view, entityx::Entity::Id parentId, entityx::Entity& node_clicked);
            int countChildNodes(entityx::EntityManager::View<Transform, SceneElement, Name> view, entityx::Entity::Id parentId);
        };
    };
};

#endif /* SceneHierarchySystem_h */
