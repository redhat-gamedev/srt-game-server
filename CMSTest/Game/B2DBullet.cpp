//
//  B2DBullet.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "B2DBullet.h"
#include "B2DWorld.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <assert.h>


// Constructor
B2DBullet::_Dependencies::_Dependencies(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity) :
    m_b2v2GunPosition(b2v2GunPosition),
    m_b2v2GunVelocity(b2v2GunVelocity)
{
    // Override the defaults where appropriate
    m_ab2BodyDef.bullet = true;
    
    // Set the size of our shape
    m_b2CircleShape.m_radius = 0.25f;
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.filter.groupIndex = -1;
    m_ab2FixtureDef.shape = &m_b2CircleShape;
    
    m_ab2BodyDef.position = b2v2GunPosition;
    m_ab2BodyDef.linearVelocity = b2v2GunVelocity;
    
    m_pb2Body = B2DWorld::Factory().CreateBody(&m_ab2BodyDef);
    m_pb2Body->CreateFixture(&m_ab2FixtureDef);
}

B2DBullet::_B2DDefinition::_B2DDefinition() :
    AB2DEntity::_AB2DDefinition()
{
    // Override the defaults where appropriate
    m_ab2BodyDef.bullet = true;
    
    // Set the size of our shape
    m_ab2CircleShape.m_radius = 0.25f;
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.filter.groupIndex = -1;
    m_ab2FixtureDef.shape = &m_ab2CircleShape;
}

B2DBullet::_B2DDefinition::_B2DDefinition(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, void* pUserData) :
    _B2DDefinition()
{
    m_ab2BodyDef.position = b2v2GunPosition;
    m_ab2BodyDef.linearVelocity = b2v2GunVelocity;
}


B2DBullet* B2DBullet::_Factory::Create(const _B2DDefinition& aB2DDefinition)
{
    b2Body*     pb2Body = NULL;
    B2DBullet*  pB2DBullet = NULL;
    
    pb2Body = CreateBody(aB2DDefinition);
    pB2DBullet = new B2DBullet(pb2Body);
    
    CreatedEvent(this, pB2DBullet);
    
    return pB2DBullet;
}

void B2DBullet::_Factory::Destroy(B2DBullet* pB2DBullet)
{
    assert(pB2DBullet);
    
    b2Body* pb2BodyCopy = pB2DBullet->m_pb2Body;
    B2DBullet* pB2DBulletCopy = pB2DBullet;
    
    DestroyedEvent(this, pB2DBulletCopy);
    B2DWorld::Factory().DestroyBody(pb2BodyCopy);
}

// Constructor(s)
B2DBullet::B2DBullet(b2Body* pb2Body) :
    AB2DEntity(pb2Body)
{
    assert(pb2Body);
}

// Constructor(s)
B2DBullet::B2DBullet(B2DBullet::_Dependencies& theDependencies) :
    AB2DEntity(theDependencies.pBody)
{
    
}

// Destructor(s)
B2DBullet::~B2DBullet()
{
    //std::cout << "B2DBullet::~B2DBullet()..." << std::endl;
}

// Helper(s)

// Method(s)
void B2DBullet::Fire(b2Vec2& b2v2FiringDirection)
{
    b2v2FiringDirection.Normalize();
    b2Vec2 b2v2Force = b2v2FiringDirection;
    b2v2Force *= 40.0f;
    m_pb2Body->ApplyForceToCenter(b2v2Force, false);
}
