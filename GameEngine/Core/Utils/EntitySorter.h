//
//  EntitySorter.h
//  GameEngine
//
//  Created by Felippe Durán on 09/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef EntitySorter_h
#define EntitySorter_h

#include <entityx.h>
#include <set>

namespace GameEngine {
    struct Transform;

    class EntitySorter {
    public:
        EntitySorter(entityx::EntityManager& entityManager) : entityManager(entityManager) {}
        
        template <typename ... Components>
        std::vector<entityx::Entity> topsort(const entityx::EntityManager::View<Transform, Components ...>& entities) {
            std::vector<entityx::Entity> sorted;
            std::set<entityx::Entity::Id> explored;
            for (entityx::Entity entity : entities) {
                if (explored.find(entity.id()) == explored.end()) dfsUtil(entity.id(), explored, sorted);
            }
            return sorted;
        };
        
    private:
        entityx::EntityManager& entityManager;
        
        void dfsUtil(entityx::Entity::Id entityId, std::set<entityx::Entity::Id>& explored, std::vector<entityx::Entity>& sorted);
    };
};

#endif /* EntitySorter_h */
