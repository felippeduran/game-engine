//
//  EditorPlayerUpdateSystem.cpp
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "EditorPlayerUpdateSystem.h"
#include "Playing.h"
#include "Engine.h"

using namespace entityx;
using namespace glm;
using namespace GameEngine::Editor;

void EditorPlayerUpdateSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Playing>([dt] (Entity entity, Playing &playing) {
        playing.engine->update(dt);
    });
};
