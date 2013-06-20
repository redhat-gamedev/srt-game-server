//
//  B2DPod.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "B2DPod.h"
//#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <assert.h>

B2DPod::_B2DDefinition          B2DPod::Definition;


B2DPod::_B2DDefinition::_B2DDefinition() :
    AB2DEntity::_AB2DDefinition()
{
    // Override the defaults where appropriate
    // Set the size of our shape
    m_ab2CircleShape.m_radius = 1.0f;
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.density = 1.0f;
    m_ab2FixtureDef.friction = 0.3f;
    m_ab2FixtureDef.restitution = 0.3f;
    m_ab2FixtureDef.filter.groupIndex = -1;
    m_ab2FixtureDef.shape = &m_ab2CircleShape;
}


// Constructor(s)
B2DPod::B2DPod(AEntity* pPlayer) :
    AB2DEntity(Definition, pPlayer)
{
}

// Destructor(s)
B2DPod::~B2DPod()
{
}

// Helper(s)

// Callback(s)

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