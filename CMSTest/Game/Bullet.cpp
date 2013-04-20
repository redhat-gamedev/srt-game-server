//
//  Bullet.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Bullet.h"
#include "UserData.h"
#include "World.h"
#include "B2DWorld.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../Shared/MakeT.h"

uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::Bullet(const std::string& strUUID, const b2Vec2& b2v2Position, b2Vec2& b2v2Direction) :
    AEntity(strUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count))
{
    ++s_ui32Count;
    CreateBullet(b2v2Position, b2v2Direction);
}

void Bullet::CreateBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction)
{
    b2BodyDef       bodyDef;
    b2CircleShape   aB2CircleShape;
    b2FixtureDef    fixtureDef;
    b2Body*         pb2bBullet = NULL;
    
	// Define the dynamic body. We set its position
	bodyDef.type = b2_dynamicBody;
    bodyDef.bullet = true;
    bodyDef.allowSleep = false;    
	bodyDef.position.Set(b2v2Position.x, b2v2Position.y);
    
    // Set the size of our shape
	aB2CircleShape.m_radius = 0.25f;
    
    // Set the fixture and use the shape
    fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.1f;
    fixtureDef.restitution = 0.1f;
    fixtureDef.filter.groupIndex = -2;
    fixtureDef.shape = &aB2CircleShape;
    
    // call the body factory.
    pb2bBullet = World::m_pB2DWorld->world->CreateBody(&bodyDef);
	pb2bBullet->CreateFixture(&fixtureDef);
    
    UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
    
    //pb2bBullet->SetUserData(&m_strUUID);
    pb2bBullet->SetUserData(pUserData);
    
    m_b2bBulletQueue.lock();
    m_b2bBulletQueue.push(pb2bBullet);
    m_b2bBulletQueue.unlock();
    
    b2Vec2 b2v2Force = b2v2Direction;
    b2v2Force.x *= 10.0f;
    b2v2Force.y *= 10.0f;
    pb2bBullet->ApplyForceToCenter(b2v2Force, false);
}

// Destructor(s)
Bullet::~Bullet()
{
    --s_ui32Count;

    m_b2bBulletQueue.lock();
    b2Body* pb2bBullet = NULL;
    while (!(m_b2bBulletQueue.empty()))
    {
        b2Body* pb2bBullet = m_b2bBulletQueue.pop();
        World::m_pB2DWorld->world->DestroyBody(pb2bBullet);
    }
    m_b2bBulletQueue.unlock();
}