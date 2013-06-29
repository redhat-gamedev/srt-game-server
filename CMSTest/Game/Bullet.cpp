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
Bullet::_Factory            Bullet::Factory;
uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::_Factory::_Factory()
{
    B2DBullet::Factory.CreatedEvent += Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletCreatedEvent);
    B2DBullet::Factory.DestroyedEvent += Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletDestroyedEvent);
}

// Destructor(s)
Bullet::_Factory::~_Factory()
{
    B2DBullet::Factory.DestroyedEvent -= Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletDestroyedEvent);
    B2DBullet::Factory.CreatedEvent -= Poco::Delegate<Bullet::_Factory, B2DBullet*&>(this, &Bullet::_Factory::HandleB2DBulletCreatedEvent);
}

void Bullet::_Factory::Create(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, b2Vec2& b2v2FiringDirection)
{
    B2DBullet::_B2DDefinition       aB2DBulletDefinition(b2v2GunPosition, b2v2GunVelocity, b2v2FiringDirection);
    B2DBullet::Factory.Create(aB2DBulletDefinition);
}

void Bullet::_Factory::Destroy(Bullet*& pBullet)
{
    assert(pBullet);
    
    B2DBullet* pB2DBullet = (B2DBullet*)pBullet->m_pB2DEntity;
    
    B2DBullet::Factory.Destroy(pB2DBullet);
}

// Event response
void Bullet::_Factory::HandleB2DBulletCreatedEvent(const void* pSender, B2DBullet*& pB2DBullet)
{
    //Bullet* pBullet = new Bullet(strUUID, b2v2GunPosition, b2v2GunVelocity, b2v2FiringDirection);
    Bullet* pBullet = new Bullet(pB2DBullet);
    pB2DBullet->ParentEntity = pBullet;
    
    CreatedEvent(this, pBullet);
}

void Bullet::_Factory::HandleB2DBulletDestroyedEvent(const void* pSender, B2DBullet*& pB2DBullet)
{
    assert(pB2DBullet);
    
    Bullet*    pBullet = (Bullet*)pB2DBullet->ParentEntity;
    
    DestroyedEvent(this, pBullet);
    delete pBullet;
    pBullet = NULL;
}

// Constructor(s)
Bullet::Bullet(B2DBullet* pB2DBullet) :
    m_bAlive(true),
    m_pLifeTimer(new Rock2D::Timer(3000)),
    AEntity(pB2DBullet, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count))
{
    assert(pB2DBullet);
    
    ++s_ui32Count;
}

//Bullet::Bullet(const std::string& strUUID, const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, b2Vec2& b2v2FiringDirection) :
//    m_bAlive(true),
//    m_pLifeTimer(new Rock2D::Timer(3000)),
//    AEntity(strUUID,
//            (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count),
//            new B2DBullet(b2v2GunPosition, b2v2GunVelocity, b2v2FiringDirection, this))
//{
//    using namespace std;
//    
//    //cout << hex << "Bullet::Bullet() " << m_ui64Tag << endl;
//
//    ++s_ui32Count;
//    
//    //EventPublisher.CreatedEvent(this, AEntity::BULLET);
//}

// Destructor(s)
Bullet::~Bullet()
{
    using namespace std;
    
    //cout << hex << "Bullet::~Bullet() " << m_ui64Tag << endl;
    
    //--s_ui32Count;
    delete m_pLifeTimer;
    m_pLifeTimer = NULL;
    
    //EventPublisher.DestroyedEvent(this, AEntity::BULLET);
}

// Method(s)

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
