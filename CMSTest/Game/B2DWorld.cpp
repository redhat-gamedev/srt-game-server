//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"
#include "Player.h"
#include "decaf/lang/Thread.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"

using namespace box2d;

B2DWorld::_Publisher                 B2DWorld::Publisher;

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
//void B2DWorld::_Publisher::OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle)
void B2DWorld::_Publisher::OnB2DWorldUpdate(b2World* pWorld)
{
    ICallbacks* pObjToCallback = NULL;
    
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        //pObjToCallback->OnB2DWorldUpdate(b2vNewPosition, fNewAngle);
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
}

// Destructor
B2DWorld::~B2DWorld()
{
    delete gravity;
    delete world;
}

// Method(s)
void B2DWorld::AddPlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    xdispatch::global_queue().sync([=]
    {
        Player* pPlayer = new Player(strUUID);
        m_listPlayers.push_front(pPlayer);
    });
}

void B2DWorld::RemovePlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    xdispatch::global_queue().sync([=]
    {
        std::list<Player*>::iterator    iterPlayerList;
        Player* pPlayer = NULL;
        
        iterPlayerList = m_listPlayers.begin();
        for (;iterPlayerList != m_listPlayers.end(); iterPlayerList++)
        {
            pPlayer = *iterPlayerList;
            if (pPlayer->ThisUUIDIsAMatch(strUUID))
            {
                m_listPlayers.erase(iterPlayerList);
                delete pPlayer;
                break;
            }
        }
    });
}

// decaf::lang::Runnable implementation
void B2DWorld::run()
{
    Player* pPlayer = NULL;
    
    while (true)
    {
        xdispatch::global_queue().sync([=]
        {
            m_listPlayersSwap = m_listPlayers;
        });
        while (!(m_listPlayersSwap.empty()))
        {
            pPlayer = m_listPlayersSwap.front();
            m_listPlayersSwap.pop_front();
            assert(pPlayer);
            pPlayer->Update();
        }
        
        // Instruct the world to perform a single step of simulation.
        // It is generally best to keep the time step and iterations fixed.
        world->Step(timeStep, velocityIterations, positionIterations);

        Publisher.OnB2DWorldUpdate(world);
        
        decaf::lang::Thread::currentThread()->sleep(15);
    }
}

