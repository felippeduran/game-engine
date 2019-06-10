//
//  EntitySorter.cpp
//  GameEngine
//
//  Created by Felippe Durán on 09/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "EntitySorter.h"
#include "Transform.h"

using namespace std;
using namespace entityx;
using namespace GameEngine;

void EntitySorter::dfsUtil(Entity::Id entityId, set<Entity::Id>& explored, vector<Entity>& sorted) {
    if (entityManager.valid(entityId)) {
        explored.insert(entityId);
        Entity entity = entityManager.get(entityId);
        if (explored.find(entity.component<Transform>()->parent) == explored.end()) dfsUtil(entity.component<Transform>()->parent, explored, sorted);
        sorted.push_back(entity);
    }
}
