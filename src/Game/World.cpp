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

#include "World.h"
#include "B2DWorld.h"
#include "AEntity.h"
#include <box2d/box2d.h>
#include <Poco/Delegate.h>
#include <assert.h>
#include "../Logging/loguru.hpp"

B2DWorld*               World::m_pB2DWorld = NULL;

using namespace box2d;
using namespace redhatgamedev::srt;


// Constructor(s)
World::Simulation::Simulation(World* pWorld) :
    m_pWorld(pWorld)
{
    assert(m_pWorld);
}

// Destructor
World::Simulation::~Simulation()
{
    assert(m_pWorld);
}

// decaf::lang::Runnable implementation
void World::Simulation::run()
{
    assert(m_pWorld);
    
    m_pWorld->Simulate();
}


// Helper(s)
void World::Setup()
{
    std::string     strWorldSimulationName = "WorldSimulationThread";
}

void World::Teardown()
{
}

// Constructor(s)
World::World()// :
{
    LOG_SCOPE_F(1, "Constructing the World");
    Setup();
}

// Destructor(s)
World::~World()
{
    Teardown();
}

void World::b2Vec2ToPbVec2(b2Vec2* pb2Vec2)
{
    assert(NULL != pb2Vec2);
}

void World::b2WorldToPbWorld(b2World* pb2World, PbWorld*& pPbWorldDefault)
{
    LOG_SCOPE_F(2, "Doing the world to world thing");
    assert(NULL != pb2World);
    assert(NULL != pPbWorldDefault);
    
    b2Fixture*  pFixtureList = NULL;
    PbBody*     pPbBody = NULL;
    PbFixture*  pPbFixture = NULL;
    PbVec2*     ppbv2Gravity = new PbVec2();
    PbVec2*     ppbv2Position = new PbVec2();
    PbVec2*     pPbVec2LinearVelocity = NULL;
    PbVec2*     pPbVec2Force = NULL;
    const       b2Vec2 b2v2Gravity = pb2World->GetGravity();
    AEntity*    pEntity = NULL;
    
    ppbv2Gravity->set_x(b2v2Gravity.x);
    ppbv2Gravity->set_y(b2v2Gravity.y);
    pPbWorldDefault->set_allocated_gravity(ppbv2Gravity);
    
    int iPreCount = 0;
    int iPostCount = 0;
    b2Body* pBodyList = pb2World->GetBodyList();
    for (b2Body* pBody = pBodyList; pBody; pBody = pBody->GetNext())
    {
        iPreCount = pPbWorldDefault->bodies_size();
        pPbBody = pPbWorldDefault->add_bodies();
        assert(NULL != pPbBody);
        iPostCount = pPbWorldDefault->bodies_size();
        assert(iPostCount > iPreCount);
        
//        pPbBody->set_active(pBody->IsActive());
        pPbBody->set_active(pBody->IsAwake());
        pPbBody->set_bullet(pBody->IsBullet());
        pPbBody->set_type(DYNAMIC);
        ppbv2Position = new PbVec2();
        ppbv2Position->set_x(pBody->GetPosition().x);
        ppbv2Position->set_y(pBody->GetPosition().y);
        pPbBody->set_angle(pBody->GetAngle());
        pPbBody->set_allocated_position(ppbv2Position);
        
        pPbVec2LinearVelocity = new PbVec2();
        pPbVec2LinearVelocity->set_x(pBody->GetLinearVelocity().x);
        pPbVec2LinearVelocity->set_y(pBody->GetLinearVelocity().y);
        pPbBody->set_allocated_linear_velocity(pPbVec2LinearVelocity);
        
        pPbVec2Force = new PbVec2();
        pPbVec2Force->set_x(0.0f);
        pPbVec2Force->set_y(0.0f);
        pPbBody->set_allocated_force(pPbVec2Force);
        
        pEntity = (AEntity*)(pBody->GetUserData().pointer);
        assert(NULL != pEntity);
        pPbBody->set_uuid(pEntity->UUID);
        pPbBody->set_tag(pEntity->Tag);
        
        pFixtureList = pBody->GetFixtureList();
        for (b2Fixture* pFixture = pFixtureList; pFixture; pFixture = pFixture->GetNext())
        {
            iPreCount = pPbBody->fixtures_size();
            pPbFixture = pPbBody->add_fixtures();
            assert(NULL != pPbFixture);
            iPostCount = pPbBody->fixtures_size();
            assert(iPostCount > iPreCount);
            
            pPbFixture->set_density(pFixture->GetDensity());
            pPbFixture->set_friction(pFixture->GetFriction());
        }
    }
}

// decaf::lang::Runnable implementation
void World::Simulate()
{
    B2DWorld::Instance().Step();
}
