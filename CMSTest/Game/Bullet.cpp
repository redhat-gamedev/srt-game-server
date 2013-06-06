//
//  Bullet.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Bullet.h"
#include "EntityData.h"
#include "World.h"
#include "B2DWorld.h"
#include "B2DWorld_BuildT.h"
#include "B2DBullet.h"
#include "Timer.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../Shared/MakeT.h"
#include <assert.h>

Bullet::_EventPublisher     Bullet::EventPublisher;
uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::Bullet(const std::string& strUUID, const b2Vec2& b2v2Position, b2Vec2& b2v2Direction) :
    m_pB2DBullet(NULL),
    m_pLifeTimer(NULL),
    AEntity(strUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count))
{
    ++s_ui32Count;
    
    m_pB2DBullet = new B2DBullet(b2v2Position, b2v2Direction, new EntityData(m_ui64Tag, m_strUUID));
    m_pLifeTimer = new Rock2D::Timer(3000);
    
    EventPublisher.CreatedEvent(this, EntityData(m_ui64Tag, m_strUUID));
}

// Destructor(s)
Bullet::~Bullet()
{
    EventPublisher.DestroyedEvent(this, EntityData(m_ui64Tag, m_strUUID));
    
    --s_ui32Count;

    delete m_pLifeTimer;
    m_pLifeTimer = NULL;
    
    delete m_pB2DBullet;
    m_pB2DBullet = NULL;
}

// Method(s)
//void Bullet::Update()
//{
//    assert(m_pLifeTimer);
//    
//    
//}
