//
//  TransformSystemTests.m
//  GameEngineTests
//
//  Created by Felippe Durán on 07/03/20.
//  Copyright © 2020 Felippe Durán. All rights reserved.
//

#import <XCTest/XCTest.h>

#include <entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "TransformSystem.h"
#include "Transform.h"

using namespace entityx;
using namespace GameEngine;
using namespace glm;

@interface TransformSystemTests : XCTestCase

@end

@implementation TransformSystemTests

EntityX *entityX;

- (void)setUp {
    entityX = new EntityX();
    entityX->systems.add<TransformSystem>();
    entityX->systems.configure();
}

- (void)tearDown {
    entityX->entities.reset();
    delete entityX;
}

Entity createEntity(vec3 position, vec3 scale, quat rotation) {
    Entity entity = entityX->entities.create();
    entity.assign<Transform>();
    entity.component<Transform>()->localPosition = position;
    entity.component<Transform>()->localScale = scale;
    entity.component<Transform>()->localRotation = rotation;
    return entity;
}

- (void)testIndependentTransforms {
    vec3 position = vec3(1.0f, 2.0f, 1.0f);
    vec3 scale = vec3(1.5f, 2.0f, 3.0f);
    quat rotation = glm::quat(glm::radians(glm::vec3(-150, -45, 0)));
    Entity entity = createEntity(position, scale, rotation);
    
    entityX->systems.update_all(1.0f/60.0f);
    
    vec3 worldPosition = vec3(entity.component<Transform>()->localToWorldMatrix * vec4(vec3(), 1));
    XCTAssertEqual(position, worldPosition);
}

- (void)testParentingTransforms {
    vec3 position = vec3(1.0f, 2.0f, 1.0f);
    vec3 scale = vec3(1.5f, 2.0f, 3.0f);
    quat rotation = glm::quat(glm::radians(glm::vec3(-150, -45, 0)));
    Entity entity = createEntity(position, scale, rotation);
    
    Entity childEntity = entityX->entities.create();
    childEntity.assign<Transform>();
    childEntity.component<Transform>()->parent = entity.id();
    
    entityX->systems.update_all(1.0f/60.0f);
    
    vec3 childWorldPosition = vec3(childEntity.component<Transform>()->localToWorldMatrix * vec4(vec3(), 1));
    XCTAssertEqual(position, childWorldPosition);
}

//- (void)testPerformanceExample {
//    // This is an example of a performance test case.
//    [self measureBlock:^{
//        // Put the code you want to measure the time of here.
//    }];
//}

@end
