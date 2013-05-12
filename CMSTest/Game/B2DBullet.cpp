//
//  B2DBullet.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "B2DBullet.h"
#include "B2DWorld.h"
#include "B2DWorld_BuildT.h"
#include "UserData.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <assert.h>

B2DBulletDefinition          B2DBulletDefinition::Definition;


B2DBulletDefinition::B2DBulletDefinition()
{
    // Define the dynamic body. We set its position
    m_ab2BodyDef.type = b2_dynamicBody;
    m_ab2BodyDef.bullet = true;
    m_ab2BodyDef.allowSleep = false;
    //m_ab2BodyDef.position.Set(b2v2Position.x, b2v2Position.y);
    
    // Set the size of our shape
    m_ab2CircleShape.m_radius = 0.25f;
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.density = 0.1f;
    m_ab2FixtureDef.friction = 0.1f;
    m_ab2FixtureDef.restitution = 0.1f;
    m_ab2FixtureDef.filter.groupIndex = -2;
    m_ab2FixtureDef.shape = &m_ab2CircleShape;
    
    //b2Vec2 b2v2Force = b2v2Direction;
    //b2v2Force.x *= 10.0f;
    //b2v2Force.y *= 10.0f;
}

// Constructor(s)
AB2DEntity::AB2DEntity() :
    m_pb2Body(NULL)
{

}

// Destructor
AB2DEntity::~AB2DEntity()
{
    xdispatch::queue("simulation").sync([=]
    {
        B2DWorld::world->DestroyBody(m_pb2Body);
    });
}

// Method(s)
void AB2DEntity::SetUserData(UserData *pUserData)
{
    assert(m_pb2Body);
    assert(pUserData);
    
    m_pb2Body->SetUserData(pUserData);
}
// Constructor(s)
B2DBullet::B2DBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction, UserData* pUserData) :
    m_b2v2InitialPosition(b2v2Position),
    m_b2v2InitialDirection(b2v2Direction),
    m_pUserData(pUserData)
{
    assert(m_pUserData);
    
    CreateBullet();
}

// Destructor(s)
B2DBullet::~B2DBullet()
{
    delete m_pUserData;
    m_pUserData = NULL;
}

// Helper(s)
void B2DBullet::CreateBullet()
{
    B2DWorld::_BuildT<B2DBullet>::B2DBody(this, &B2DBullet::OnB2DBodyCreated, B2DBulletDefinition::Definition.BodyDef, B2DBulletDefinition::Definition.FixtureDef);
}

// Callback(s)
void B2DBullet::OnB2DBodyCreated(b2Body* pb2bBullet)
{
    assert(pb2bBullet);
    assert(NULL == m_pb2Body);
    
    m_pb2Body = pb2bBullet;
    
    m_pb2Body->SetTransform(m_b2v2InitialPosition, 0.0f);
    b2Vec2 b2v2Force = m_b2v2InitialDirection;
    b2v2Force.x *= 10.0f;
    b2v2Force.y *= 10.0f;
    m_pb2Body->ApplyForceToCenter(b2v2Force, false);
    
    m_pb2Body->SetUserData(m_pUserData);
}
