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

void EntitySorter::dfsUtil(Entity entity, set<Entity::Id>& explored, vector<Entity>& sorted) {
    if (entity.valid()) {
        explored.insert(entity.id());
        Entity parent = entity.component<Transform>()->parent;
        if (explored.find(parent.id()) == explored.end()) dfsUtil(parent, explored, sorted);
        sorted.push_back(entity);
    }
}
