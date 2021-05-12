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
#include "../Logging/loguru.hpp"
#include "../Application/Configuration.h"


// Constructor
B2DPod::_Dependencies::_Dependencies(const b2Vec2& b2v2Position) :
    m_b2v2Position(b2v2Position)
{
    // Override the defaults where appropriate
    // Set the size of our shape
    //m_b2CircleShape.m_radius = 90.0f;
    // half width and half height
    m_b2PolygonShape.SetAsBox(Configuration::Instance().ShipWidth / 2, Configuration::Instance().ShipLength / 2);
    
    // Set the fixture and use the shape

    // the density multiplied by the area produces the resultant mass of the fixture
    //
    m_ab2FixtureDef.density = Configuration::Instance().FixtureDensity;

//    m_ab2FixtureDef.friction = 0.3f;
//    m_ab2FixtureDef.restitution = 0.3f;
    //m_ab2FixtureDef.filter.groupIndex = -1;
    m_ab2FixtureDef.filter.categoryBits = POD;//0x0002;
    //m_ab2FixtureDef.filter.maskBits = BOUNDARY | BULLET;//0x0004;
    m_ab2FixtureDef.filter.maskBits = BOUNDARY | POD | BULLET;
    m_ab2FixtureDef.shape = &m_b2PolygonShape;
    
    m_ab2BodyDef.position = b2v2Position;
}


// Constructor(s)
B2DPod::B2DPod(B2DPod::_Dependencies& theDependencies) :
    AB2DEntity(B2DWorld::Factory().CreateBody(&theDependencies.BodyDef))
{
    LOG_SCOPE_FUNCTION(4);
    b2Fixture* pbFixture = m_pb2Body->CreateFixture(&theDependencies.FixtureDef);
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
    
    LOG_F(6, "Force being applied: %f x %f", fX, fY);
    b2v2Move.x = fX;
    b2v2Move.y = fY;
    
    m_b2v2MoveQueueMutex.lock();
    m_b2v2MoveQueue.push(b2v2Move);
    m_b2v2MoveQueueMutex.unlock();
}

void B2DPod::Update()
{
    Configuration &config = Configuration::Instance();

    m_b2v2MoveQueueMutex.lock();
    LOG_F(3, "Our current linear velocity: %f x %f", m_pb2Body->GetLinearVelocity().x, m_pb2Body->GetLinearVelocity().y);
    LOG_F(3, "Our current angular velocity: %f", m_pb2Body->GetAngularVelocity());
    LOG_F(3, "Our current position: %f x %f", m_pb2Body->GetPosition().x, m_pb2Body->GetPosition().y);
    LOG_F(3, "Our current angle: %f", m_pb2Body->GetAngle());
    LOG_F(6, "Emptying the b2v2 move queue");
    while (!(m_b2v2MoveQueue.empty()))
    {
        b2Vec2 ab2Vec2Move = m_b2v2MoveQueue.front();
        m_b2v2MoveQueue.pop();
        LOG_SCOPE_F(6, "Calculating the forces");

        // a thrust vector for applying in the direction the ship is facing
        // using sin/cos on the angle of the ship
        // https://gamedev.stackexchange.com/questions/56881/moving-a-box2d-object-in-the-direction-it-is-facing-using-applyforce
        b2Vec2 m_b2v2_thrust;

        // if the x portion of the input is zero, then this ends up zeroed out
        m_b2v2_thrust.x = cos(m_pb2Body->GetAngle()) * ab2Vec2Move.x;
        m_b2v2_thrust.y = sin(m_pb2Body->GetAngle()) * ab2Vec2Move.x;
        m_b2v2_thrust.x *= config.ForceMultiplier;
        m_b2v2_thrust.y *= config.ForceMultiplier;

        LOG_F(6, "Force applied to center: %f x %f", m_b2v2_thrust.x, m_b2v2_thrust.y);
        m_pb2Body->ApplyForceToCenter(m_b2v2_thrust, true);


        // TODO: change to 180deg / 4sec in some calculation against the server cycle
        // TODO: config base turn rate

        // turn rate is in degrees per second
        // server cycle is in milliseconds, so divide it by 1000
        // effective turn per tick = turn rate * server cycle / 1000
        float m_fDegreesPerTick = 45.0f * float(Configuration::Instance().SleepCycle) / 1000.0f;

        // for really high sleep cycles, even with a single button press, this
        // ends up being a really high value, so max it out at 5 degrees

        if (m_fDegreesPerTick > 5.0f) {
            m_fDegreesPerTick = 5.0f;
        }
        LOG_F(6, "Turn degrees per tick: %f", m_fDegreesPerTick);

        // depending on whether the player is requesting left or right rotation, multiply by
        // the received y value
        m_fDegreesPerTick *= float(ab2Vec2Move.y);
        LOG_F(6, "Turn in Degrees: %f", ab2Vec2Move.y);

        // convert to radians
        m_fDegreesPerTick *= ((22.0 / 7.0) / 180.0); // Pi is 22/7 
        LOG_F(6, "Turn amount in radians: %f", m_fDegreesPerTick);
        LOG_F(6, "Current angle: %f", m_pb2Body->GetAngle());

        // rotate the ship by the effective degrees every tick
        m_pb2Body->SetTransform(m_pb2Body->GetPosition(), m_pb2Body->GetAngle() + m_fDegreesPerTick);

    }
    m_b2v2MoveQueueMutex.unlock();
}
