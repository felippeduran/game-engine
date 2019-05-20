//
//  EditorCamera.h
//  GameEngine
//
//  Created by Felippe Durán on 10/08/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#ifndef EditorCamera_h
#define EditorCamera_h

#include <rttr/registration>

using namespace rttr;

namespace GameEngine {
    namespace Editor {
        struct EditorCamera {};
    };
};

RTTR_REGISTRATION
{
    registration::class_<GameEngine::Editor::EditorCamera>("EditorCamera")
    .constructor<>();
}


#endif /* EditorCamera_h */
