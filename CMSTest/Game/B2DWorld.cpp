//
//  B2DWorld.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-30.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "B2DWorld.h"
#include "B2DBullet.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include "Poco/ScopedLock.h"
#include <assert.h>

b2World*                            B2DWorld::s_pb2World = NULL;
Poco::Mutex                         B2DWorld::s_aMutex;


// Constructor(s)
//B2DWorld::_Factory::_Factory()
//{
//
//}

// Destructor(s)
//B2DWorld::_Factory::~_Factory()
//{
//
//}

b2Body* B2DWorld::_Factory::CreateBody(const b2BodyDef* pb2BodyDef)
{
    using namespace Poco;
    
    assert(pb2BodyDef);
    assert(s_pb2World);
    
    b2Body* pb2Body = NULL;
    
    ScopedLock<Mutex> aScopedLock(s_aMutex);
    pb2Body = s_pb2World->CreateBody(pb2BodyDef);
    
    return pb2Body;
}

void B2DWorld::_Factory::DestroyBody(b2Body* pb2Body)
{
    using namespace Poco;

    assert(pb2Body);
    assert(s_pb2World);
    
    ScopedLock<Mutex> aScopedLock(s_aMutex);
    s_pb2World->DestroyBody(pb2Body);
}

b2Joint* B2DWorld::_Factory::CreateJoint(const b2JointDef* pb2JointDef)
{
    using namespace Poco;
    
    assert(pb2JointDef);
    assert(s_pb2World);
    
    b2Joint* pb2Joint = NULL;
    
    ScopedLock<Mutex> aScopedLock(s_aMutex);
    pb2Joint = s_pb2World->CreateJoint(pb2JointDef);
    
    return pb2Joint;
}

void B2DWorld::_Factory::DestroyJoint(b2Joint* pb2Joint)
{
    using namespace Poco;
    
    assert(pb2Joint);
    assert(s_pb2World);
    
    ScopedLock<Mutex> aScopedLock(s_aMutex);
    s_pb2World->DestroyJoint(pb2Joint);
}

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
    s_pb2World = new b2World(*gravity);
    
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
    
    delete s_pb2World;
    s_pb2World = NULL;
}

// Method(s)
void B2DWorld::Step()
{
    using namespace Poco;
    
    ScopedLock<Mutex> aScopedLock(s_aMutex);
    s_pb2World->Step(timeStep, velocityIterations, positionIterations);
}
