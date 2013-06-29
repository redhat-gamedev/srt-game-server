//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"

b2World*                            B2DWorld::world = NULL;


// Constructor(s)
B2DWorld::B2DWorld() :
    gravity(new b2Vec2(0.0f, 0.0f)),
    timeStep(1.0f / 66.0f),
    velocityIterations(6),
    positionIterations(2),
//    world(new b2World(*gravity)),
    m_pBox2DSerialDispatchQueue(new xdispatch::queue("box2d"))
{
    //gravity = new b2Vec2(0.0f, -9.81f);
//    gravity = new b2Vec2(0.0f, 0.0f);
    world = new b2World(*gravity);
    
    // As per https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking
    // resulting in 15ms per timeStep or tick
//	timeStep = 1.0f / 66.0f;
    
//	velocityIterations = 6;
//	positionIterations = 2;
    
//    m_pBox2DSerialDispatchQueue = new xdispatch::queue("box2d");
}

// Destructor
B2DWorld::~B2DWorld()
{
    delete m_pBox2DSerialDispatchQueue;
    m_pBox2DSerialDispatchQueue = NULL;

    delete gravity;
    gravity = NULL;
    
    delete world;
    world = NULL;
}

// Method(s)
void B2DWorld::Step()
{
    m_pBox2DSerialDispatchQueue->sync([=]
    {
        world->Step(timeStep, velocityIterations, positionIterations);
    });
}
