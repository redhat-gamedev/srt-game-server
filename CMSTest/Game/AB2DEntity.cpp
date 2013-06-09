//
//  AB2DEntity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AB2DEntity.h"
#include "B2DWorld.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"


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
AB2DEntity::AB2DEntity(const _AB2DDefinition& aAB2DDefinition) :
    m_pb2Body(NULL)
{
    m_pb2Body = B2DWorld::world->CreateBody(&aAB2DDefinition.BodyDef);
    m_pb2Body->CreateFixture(&aAB2DDefinition.FixtureDef);
}

// Destructor
AB2DEntity::~AB2DEntity()
{
    B2DWorld::world->DestroyBody(m_pb2Body);
    m_pb2Body = NULL;
}

// Method(s)
//void AB2DEntity::SetEntityData(EntityData *pEntityData)
//{
//    assert(m_pb2Body);
//    assert(pEntityData);
//    
//    m_pb2Body->SetUserData(pEntityData);
//}

// Method(s)
