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

#include "B2DPod.h"
#include "B2DWorld.h"
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <assert.h>


// Constructor
B2DPod::_Dependencies::_Dependencies(const b2Vec2& b2v2Position) :
    m_b2v2Position(b2v2Position)
{
    // Override the defaults where appropriate
    // Set the size of our shape
    m_b2CircleShape.m_radius = 2.0f;
    
    // Set the fixture and use the shape
//    m_ab2FixtureDef.density = 1.0f;
//    m_ab2FixtureDef.friction = 0.3f;
//    m_ab2FixtureDef.restitution = 0.3f;
    //m_ab2FixtureDef.filter.groupIndex = -1;
    m_ab2FixtureDef.filter.categoryBits = POD;//0x0002;
    //m_ab2FixtureDef.filter.maskBits = BOUNDARY | BULLET;//0x0004;
    m_ab2FixtureDef.filter.maskBits = BOUNDARY | POD | BULLET;
    m_ab2FixtureDef.shape = &m_b2CircleShape;
    
    m_ab2BodyDef.position = b2v2Position;
}


// Constructor(s)
B2DPod::B2DPod(B2DPod::_Dependencies& theDependencies) :
    AB2DEntity(B2DWorld::Factory().CreateBody(&theDependencies.BodyDef))
{
    m_pb2Body->CreateFixture(&theDependencies.FixtureDef);
    m_pb2Fixture = m_pb2Body->GetFixtureList();
}

// Destructor(s)
B2DPod::~B2DPod()
{
}

// Method(s)
void B2DPod::Move(float fX, float fY)
{
    b2Vec2 b2v2Move;
    
    b2v2Move.x = fX;
    b2v2Move.y = fY;
    
    m_b2v2MoveQueue.lock();
    m_b2v2MoveQueue.push(b2v2Move);
    m_b2v2MoveQueue.unlock();
}

void B2DPod::Update()
{
    m_b2v2MoveQueue.lock();
    while (!(m_b2v2MoveQueue.empty()))
    {
        b2Vec2 ab2Vec2Move = m_b2v2MoveQueue.pop();
        ab2Vec2Move.x *= 50.0f;
        ab2Vec2Move.y *= 50.0f;
        m_pb2Body->ApplyForceToCenter(ab2Vec2Move, true);
    }
    m_b2v2MoveQueue.unlock();    
}