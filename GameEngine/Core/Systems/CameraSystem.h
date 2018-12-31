//
//  CameraSystem.h
//  GameEngine
//
//  Created by Felippe Durán on 24/08/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#ifndef CameraSystem_h
#define CameraSystem_h

#include <entityx.h>
#include <glm/glm.hpp>

namespace GameEngine {
    struct CameraSystem : public entityx::System<CameraSystem> {
        void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
        
    private:
        void updateRenderers(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt, glm::mat4& projection, glm::mat4& view, glm::vec3& viewPosition);
    };
};

#endif /* CameraSystem_h */
