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
#include "B2DWorld_BuildT.h"
#include "B2DBullet.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../Shared/MakeT.h"

uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::Bullet(const std::string& strUUID, const b2Vec2& b2v2Position, b2Vec2& b2v2Direction) :
    m_pB2DBullet(NULL),
    AEntity(strUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count))
{
    ++s_ui32Count;
    
    m_pB2DBullet = new B2DBullet(b2v2Position, b2v2Direction, new UserData(m_ui64Tag, m_strUUID));
}

// Destructor(s)
Bullet::~Bullet()
{
    --s_ui32Count;

//    m_b2bBulletQueue.lock();
//    b2Body* pb2bBullet = NULL;
//    while (!(m_b2bBulletQueue.empty()))
//    {
//        pb2bBullet = m_b2bBulletQueue.pop();
//        B2DWorld::world->DestroyBody(pb2bBullet);
//    }
//    m_b2bBulletQueue.unlock();
    
    delete m_pB2DBullet;
    m_pB2DBullet = NULL;
}

//void Bullet::CreateBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction)
//{
//    B2DWorld::_BuildT<Bullet>::B2DBody(this, &Bullet::OnB2DBodyCreated, B2DBullet::Definition.BodyDef, B2DBullet::Definition.FixtureDef);
//}
//
//void Bullet::OnB2DBodyCreated(b2Body* pb2bBullet)
//{
//    assert(pb2bBullet);
//    
//    pb2bBullet->SetUserData(new UserData(m_ui64Tag, m_strUUID));
//
//    pb2bBullet->SetTransform(m_b2v2InitialPosition, 0.0f);
//    b2Vec2 b2v2Force = m_b2v2InitialDirection;
//    b2v2Force.x *= 10.0f;
//    b2v2Force.y *= 10.0f;
//    pb2bBullet->ApplyForceToCenter(b2v2Force, false);
//    
//    m_b2bBulletQueue.lock();
//    m_b2bBulletQueue.push(pb2bBullet);
//    m_b2bBulletQueue.unlock();
//}
