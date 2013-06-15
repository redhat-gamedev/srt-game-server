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
    m_ab2FixtureDef.filter.groupIndex = -2;
    m_ab2FixtureDef.shape = &m_ab2CircleShape;
}


// Constructor(s)
B2DBullet::B2DBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction, AEntity* pBullet) :
    m_b2v2InitialPosition(b2v2Position),
    m_b2v2InitialDirection(b2v2Direction),
    AB2DEntity(Definition, pBullet)
{
    m_pb2Body->SetTransform(m_b2v2InitialPosition, 0.0f);
    
    b2Vec2 b2v2Force = m_b2v2InitialDirection;
    b2v2Force.x *= 20.0f;
    b2v2Force.y *= 20.0f;
    m_pb2Body->ApplyForceToCenter(b2v2Force, false);
}

// Destructor(s)
B2DBullet::~B2DBullet()
{
    //std::cout << "B2DBullet::~B2DBullet()..." << std::endl;
}

// Helper(s)
