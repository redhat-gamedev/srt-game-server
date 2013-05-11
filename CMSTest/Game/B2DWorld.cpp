//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"
#include "UserData.h"

B2DWorld::_Publisher                B2DWorld::Publisher;
b2World*                            B2DWorld::world = NULL;
//xdispatch::synclock                 B2DWorld::aSyncLock;
//xdispatch::synclock*                B2DWorld::s_pSyncLock = NULL;

// Constructor(s)
/*
 B2DWorld.h::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 B2DWorld.h::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void B2DWorld::_Publisher::OnB2DWorldUpdate(b2World* pWorld)
{
    ICallbacks* pObjToCallback = NULL;
    
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnB2DWorldUpdate(pWorld);
    }
}

void B2DWorld::_Publisher::OnB2DWorldBodyUpdate(b2Body* pBody)
{
    ICallbacks* pObjToCallback = NULL;
    
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnB2DWorldBodyUpdate(pBody);
    }
}

// Constructor(s)
B2DWorld::B2DWorld()
{
    //gravity = new b2Vec2(0.0f, -9.81f);
    gravity = new b2Vec2(0.0f, 0.0f);
    world = new b2World(*gravity);
    
    // As per https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking
    // resulting in 15ms per timeStep or tick
	timeStep = 1.0f / 66.0f;
    
	velocityIterations = 6;
	positionIterations = 2;
    
    //s_pSyncLock = new xdispatch::synclock();
}

// Destructor
B2DWorld::~B2DWorld()
{
    delete gravity;
    gravity = NULL;
    
    delete world;
    world = NULL;
}

// Method(s)

// decaf::lang::Runnable implementation
void B2DWorld::run()
{    
    // Instruct the world to perform a single step of simulation.
    // It is generally best to keep the time step and iterations fixed.
    //aSyncLock.lock();
    //synchronize ("B2DWorld_lock")
    //XDISPATCH_SYNCHRONIZED
    //s_pSyncLock->lock();
    xdispatch::global_queue().sync([=]
    {
        world->Step(timeStep, velocityIterations, positionIterations);
    });
    //aSyncLock.unlock();
    //s_pSyncLock->unlock();
    
    Publisher.OnB2DWorldUpdate(world);
}

