//
//  Bullet.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Bullet.h"
#include "B2DWorld.h"
#include "B2DBullet.h"
#include "Timer.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include "../Shared/MakeT.h"
#include "Poco/Delegate.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>

Bullet::_EventPublisher     Bullet::EventPublisher;
uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::_Factory::_Factory()
{
//    B2DBullet::Factory().CreatedEvent += Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletCreatedEvent);
//    B2DBullet::Factory().DestroyedEvent += Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletDestroyedEvent);
}

// Destructor(s)
Bullet::_Factory::~_Factory()
{
//    B2DBullet::Factory().DestroyedEvent -= Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletDestroyedEvent);
//    B2DBullet::Factory().CreatedEvent -= Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletCreatedEvent);
}

Bullet* Bullet::_Factory::Create(const std::string& strParentUUID, const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity)
{
    B2DBullet::_B2DDefinition       aB2DBulletDefinition(b2v2GunPosition, b2v2GunVelocity);
    B2DBullet* pB2DBullet = B2DBullet::Factory().Create(aB2DBulletDefinition);
    Bullet* pBullet = new Bullet(strParentUUID, pB2DBullet);
    pB2DBullet->SetParentEntity(pBullet);
    CreatedEvent(this, pBullet);
    
    return pBullet;
}

void Bullet::_Factory::Destroy(Bullet*& pBullet)
{
    assert(pBullet);
    
    B2DBullet* pB2DBullet = (B2DBullet*)pBullet->m_pB2DEntity;
    B2DBullet::Factory().Destroy(pB2DBullet);

    DestroyedEvent(this, pBullet);
    delete pBullet;
    pBullet = NULL;
}

// Event response
//void Bullet::_Factory::HandleB2DBulletCreatedEvent(const void* pSender, B2DBullet*& pB2DBullet)
//{
//    Bullet* pBullet = new Bullet(pB2DBullet);
//    pB2DBullet->SetParentEntity(pBullet);
//    
//    CreatedEvent(this, pBullet);
//}
//
//void Bullet::_Factory::HandleB2DBulletDestroyedEvent(const void* pSender, B2DBullet*& pB2DBullet)
//{
//    assert(pB2DBullet);
//    
//    Bullet*    pBullet = (Bullet*)pB2DBullet->GetParentEntity();
//    
//    DestroyedEvent(this, pBullet);
//    delete pBullet;
//    pBullet = NULL;
//}

// Constructor(s)
Bullet::Bullet(const std::string& strParentUUID, B2DBullet* pB2DBullet) :
    m_bAlive(true),
    m_pLifeTimer(new Rock2D::Timer(3000)),
    AEntity(strParentUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count), pB2DBullet)
{
    assert(pB2DBullet);

    //cout << hex << "Bullet::Bullet() " << m_ui64Tag << endl;
    
    ++s_ui32Count;
}

// Destructor(s)
Bullet::~Bullet()
{
    using namespace std;
    
    //cout << hex << "Bullet::~Bullet() " << m_ui64Tag << endl;
    
    //--s_ui32Count;
    delete m_pLifeTimer;
    m_pLifeTimer = NULL;
}

// Method(s)
void Bullet::Fire(b2Vec2& b2v2FiringDirection)
{
    assert(m_pB2DEntity);
    
    ((B2DBullet*)m_pB2DEntity)->Fire(b2v2FiringDirection);
}


// Override(s)
void Bullet::Update()
{
    assert(m_pLifeTimer);

    if (m_pLifeTimer->Status() == Rock2D::Timer::EXPIRED)
    {
        m_bAlive = false;
    }
    
    EventPublisher.UpdatedEvent(this, AEntity::BULLET);
}
