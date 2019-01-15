//
//  Project.h
//  EngineEditor
//
//  Created by Felippe Durán on 06/01/19.
//  Copyright © 2019 Felippe Durán. All rights reserved.
//

#ifndef Project_h
#define Project_h

namespace GameEngine {
    namespace Editor {
        struct Project {
            Project(std::string name, void *sharedObject) : name(name), sharedObject(sharedObject) {};
            
            std::string name;
            void *sharedObject;
        };
    };
};


#endif /* Project_h */
