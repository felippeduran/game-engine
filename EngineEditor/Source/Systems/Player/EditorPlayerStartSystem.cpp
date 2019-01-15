//
//  EditorPlayerStartSystem.cpp
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#include "EditorPlayerStartSystem.h"
#include "Play.h"
#include "Playing.h"
#include "Project.h"
#include "Engine.h"

#include <dlfcn.h>

using namespace entityx;
using namespace GameEngine::Editor;

void EditorPlayerStartSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Play>([this, &es] (Entity entity, Play &play) {
        es.each<Project>([this, &entity] (Entity entityProject, Project &project) {
            Engine *engine = new Engine(inputHandler);
            entity.assign<Playing>(engine);
            engine->initialize();
            engine->configure();
            
            typedef int (*game_initialize)(Engine *engine);
            game_initialize initialize = (game_initialize)dlsym(project.sharedObject, "initialize");
            if (initialize == NULL) printf("%s\n", dlerror());
            else initialize(engine);
        });
        
        entity.remove<Play>();
    });
};
