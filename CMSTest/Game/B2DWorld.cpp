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

//template <class T>
//void B2DWorld::_BuildT<T>::B2DPod(T* pT, void (T::*pB2DPodCreated)(b2Body* pb2bPod), UserData* pUserData)
//{
//    b2BodyDef       bodyDef;
//    b2PolygonShape  dynamicBox;
//    b2CircleShape   aB2CircleShape;
//    b2FixtureDef    fixtureDef;
//    b2Body*         pb2bPod = NULL;
//    
//	// Define the dynamic body. We set its position
//	bodyDef.type = b2_dynamicBody;
//	bodyDef.position.Set(0.0f, 0.0f);
//    
//    // Set the size of our shape
//	aB2CircleShape.m_radius = 1.0f;
//    
//    // Set the fixture and use the shape
//    fixtureDef.density = 1.0f;
//	fixtureDef.friction = 0.3f;
//    fixtureDef.restitution = 0.3f;
//    fixtureDef.filter.groupIndex = -2;
//    fixtureDef.shape = &aB2CircleShape;
//    
//    //UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
//    
//    // call the body factory.
////    m_pb2bPod = World::m_pB2DWorld->world->CreateBody(&bodyDef);
////	m_pb2bPod->CreateFixture(&fixtureDef);
////    m_pb2bPod->SetUserData(pUserData);
//    
//    pb2bPod = world->CreateBody(&bodyDef);
//	pb2bPod->CreateFixture(&fixtureDef);
//    pb2bPod->SetUserData(pUserData);
//
//    (pT->* pB2DPodCreated)(pb2bPod);
//}

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
    world->Step(timeStep, velocityIterations, positionIterations);
    Publisher.OnB2DWorldUpdate(world);
}

