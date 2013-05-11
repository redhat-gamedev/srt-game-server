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

// Destructor(s)
Bullet::~Bullet()
{
    --s_ui32Count;

    m_b2bBulletQueue.lock();
    b2Body* pb2bBullet = NULL;
    while (!(m_b2bBulletQueue.empty()))
    {
        pb2bBullet = m_b2bBulletQueue.pop();
        B2DWorld::world->DestroyBody(pb2bBullet);
    }
    m_b2bBulletQueue.unlock();
}

void Bullet::CreateBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction)
{
    //UserData* pUserData = new UserData(m_ui64Tag, m_strUUID);
    B2DWorld::_BuildT<Bullet>::B2DBullet(this, &Bullet::OnBuildB2DBulletCompleted, b2v2Position, b2v2Direction);
}

void Bullet::OnBuildB2DBulletCompleted(b2Body* pb2bBullet)
{
    assert(pb2bBullet);
    
    pb2bBullet->SetUserData(new UserData(m_ui64Tag, m_strUUID));
    
    m_b2bBulletQueue.lock();
    m_b2bBulletQueue.push(pb2bBullet);
    m_b2bBulletQueue.unlock();
}
