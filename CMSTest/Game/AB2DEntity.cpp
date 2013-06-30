//
//  AB2DEntity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AB2DEntity.h"
#include "B2DWorld.h"
#include "AEntity.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <assert.h>

AB2DEntity::_Serializer                 AB2DEntity::Serializer;
//AB2DEntity::_Factory                    AB2DEntity::Factory;

using namespace gameevent;


void AB2DEntity::_Serializer::Serialize(const AB2DEntity* pB2DEntity, gameevent::EntityGameEvent* pEntityGameEvent)
{
    using namespace box2d;
    
    assert(pEntityGameEvent);
    
    //int iPreCount = 0;
    //int iPostCount = 0;
    
    b2Fixture*  pFixtureList = NULL;
    PbBody*     pPbBody = NULL;
    PbFixture*  pPbFixture = NULL;
    //PbVec2*     ppbv2Gravity = new PbVec2();
    PbVec2*     ppbv2Position = new PbVec2();
    PbVec2*     pPbVec2LinearVelocity = NULL;
    PbVec2*     pPbVec2Force = NULL;
    //const       b2Vec2 b2v2Gravity = pb2World->GetGravity();
    AEntity*    pEntity = NULL;
    
    pPbBody = pEntityGameEvent->mutable_body();

    pPbBody->set_active(pB2DEntity->m_pb2Body->IsActive());
    pPbBody->set_bullet(pB2DEntity->m_pb2Body->IsBullet());
    pPbBody->set_type(DYNAMIC);
    ppbv2Position = new PbVec2();
    ppbv2Position->set_x(pB2DEntity->m_pb2Body->GetPosition().x);
    ppbv2Position->set_y(pB2DEntity->m_pb2Body->GetPosition().y);
    pPbBody->set_angle(pB2DEntity->m_pb2Body->GetAngle());
    pPbBody->set_allocated_position(ppbv2Position);
    
    pPbVec2LinearVelocity = new PbVec2();
    pPbVec2LinearVelocity->set_x(pB2DEntity->m_pb2Body->GetLinearVelocity().x);
    pPbVec2LinearVelocity->set_y(pB2DEntity->m_pb2Body->GetLinearVelocity().y);
    pPbBody->set_allocated_linear_velocity(pPbVec2LinearVelocity);
    
    pPbVec2Force = new PbVec2();
    pPbVec2Force->set_x(0.0f);
    pPbVec2Force->set_y(0.0f);
    pPbBody->set_allocated_force(pPbVec2Force);
    
    pEntity = static_cast<AEntity*>(pB2DEntity->m_pb2Body->GetUserData());
    assert(NULL != pEntity);
    pPbBody->set_uuid(pEntity->UUID);
    pPbBody->set_tag(pEntity->Tag);
    
    pFixtureList = pB2DEntity->m_pb2Body->GetFixtureList();
    for (b2Fixture* pFixture = pFixtureList; pFixture; pFixture = pFixture->GetNext())
    {
        //iPreCount = pPbBody->fixtures_size();
        pPbFixture = pPbBody->add_fixtures();
        assert(NULL != pPbFixture);
        //iPostCount = pPbBody->fixtures_size();
        //assert(iPostCount > iPreCount);
        
        pPbFixture->set_density(pFixture->GetDensity());
        pPbFixture->set_friction(pFixture->GetFriction());
    }
}

void AB2DEntity::_Serializer::Deserialisze(const gameevent::EntityGameEvent* pEntityGameEvent, AB2DEntity*& pEntity)
{
    
    
}

b2Body* AB2DEntity::_Factory::CreateBody(const _AB2DDefinition& aAB2DDefinition)
{
    b2Body* pb2Body = B2DWorld::Factory().CreateBody(&aAB2DDefinition.BodyDef);
    pb2Body->CreateFixture(&aAB2DDefinition.FixtureDef);
    pb2Body->SetUserData((void *)aAB2DDefinition.UserData);
    
    return pb2Body;
}

AB2DEntity::_AB2DDefinition::_AB2DDefinition()
{
    // Define the dynamic body. We set its position
    m_ab2BodyDef.type = b2_dynamicBody;
    m_ab2BodyDef.bullet = false;
    m_ab2BodyDef.allowSleep = false;
    m_ab2BodyDef.position.Set(0.0f, 0.0f);
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.density = 0.1f;
    m_ab2FixtureDef.friction = 0.1f;
    m_ab2FixtureDef.restitution = 0.1f;
    m_ab2FixtureDef.filter.groupIndex = 0;
}


// Constructor(s)
AB2DEntity::AB2DEntity()
{
    assert(false);
}

AB2DEntity::AB2DEntity(b2Body* pb2Body) :
    m_pb2Body(pb2Body)
{
    assert(m_pb2Body);
}

AB2DEntity::AB2DEntity(const _AB2DDefinition& aAB2DDefinition, AEntity* pEntity) :
    m_pb2Body(NULL)
{
    assert(pEntity);
    
    m_pb2Body = B2DWorld::Factory().CreateBody(&aAB2DDefinition.BodyDef);
    m_pb2Body->CreateFixture(&aAB2DDefinition.FixtureDef);
    m_pb2Body->SetUserData((void *)pEntity);
}

void AB2DEntity::SetParentEntity(AEntity* pParentEntity)
{
    assert(pParentEntity);
    
    m_pParentEntity = pParentEntity;
    if (m_pb2Body)
    {
        m_pb2Body->SetUserData((void*)pParentEntity);
    }
}

// Destructor
AB2DEntity::~AB2DEntity()
{
    //std::cout << "AB2DEntity::~AB2DEntity()..." << std::endl;
    
    B2DWorld::Factory().DestroyBody(m_pb2Body);
    m_pb2Body = NULL;
}

// Method(s)
