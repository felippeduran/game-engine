//
//  EditorPlayerStopSystem.cpp
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "EditorPlayerStopSystem.h"
#include "Stop.h"
#include "Playing.h"
#include "Engine.h"

using namespace entityx;
using namespace GameEngine::Editor;

void EditorPlayerStopSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Playing, Stop>([this] (Entity entity, Playing &playing, Stop &stop) {
        playing.engine->cleanup();
        entity.remove<Playing>();
        entity.remove<Stop>();
    });
};
