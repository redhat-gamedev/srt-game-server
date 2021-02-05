//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "B2DWorld.h"
#include "B2DBullet.h"
#include <Poco/ScopedLock.h>
#include <assert.h>
#include "../Logging/loguru.hpp"

b2World*                            B2DWorld::s_pb2World = NULL;
Poco::Mutex                         B2DWorld::s_aMutex;


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
    // As per https://developer.valvesoftware.com/wiki/Source_Multiplayer_Networking
    // resulting in 15ms per timeStep or tick
    velocityIterations(6),
    positionIterations(2)
{
    LOG_SCOPE_F(1, "Constructing the Box2D world");
    s_pb2World = new b2World(*gravity);
}

// Destructor
B2DWorld::~B2DWorld()
{
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
    LOG_SCOPE_F(2, "Stepping the game world");
    s_pb2World->Step(timeStep, velocityIterations, positionIterations);
}
