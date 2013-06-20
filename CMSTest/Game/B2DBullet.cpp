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

B2DBullet::_B2DDefinition          B2DBullet::Definition;


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


// Constructor(s)
B2DBullet::B2DBullet(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, b2Vec2& b2v2FiringDirection, AEntity* pBullet) :
    m_b2v2InitialPosition(b2v2GunPosition),
    m_b2v2InitialVelocity(b2v2GunVelocity),
    AB2DEntity(Definition, pBullet)
{
    m_pb2Body->SetTransform(m_b2v2InitialPosition, 0.0f);
    
    //float fSpeed = b2v2FiringDirection.Normalize();
    b2v2FiringDirection.Normalize();
    b2Vec2 b2v2Force = b2v2FiringDirection;
    b2v2Force *= 40.0f;
    b2v2Force += b2v2GunVelocity;
    m_pb2Body->ApplyForceToCenter(b2v2Force, false);
}

// Destructor(s)
B2DBullet::~B2DBullet()
{
    //std::cout << "B2DBullet::~B2DBullet()..." << std::endl;
}

// Helper(s)
