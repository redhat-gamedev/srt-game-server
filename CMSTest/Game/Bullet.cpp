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
#include "../Shared/MakeT.h"
#include "Poco/Delegate.h"
//#include <iostream>
//#include <iomanip>
#include <string>
#include <assert.h>

Poco::BasicEvent<Bullet*&>  Bullet::UpdatedEvent;
uint32_t                    Bullet::s_ui32Count = 1;


// Constructor(s)
Bullet::_Dependencies::_Dependencies(const std::string& strParentUUID, B2DBullet* pB2DBullet) :
    m_strParentUUID(strParentUUID),
    m_pB2DBullet(pB2DBullet)
{
    assert(strParentUUID.length() > 0);
    assert(pB2DBullet);
}


// Constructor(s)
Bullet::Bullet(_Dependencies& theDependencies) :
    m_bAlive(true),
    m_pLifeTimer(new Rock2D::Timer(3000)),
    AEntity(theDependencies.ParentUUID,
            (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::BULLET, s_ui32Count), theDependencies.pB2DBullet)
{
    assert(m_pB2DEntity);

    //cout << hex << "Bullet::Bullet() " << m_ui64Tag << endl;
    
    ++s_ui32Count;
    
    m_pB2DEntity->SetParentEntity(this);
}

// Destructor(s)
Bullet::~Bullet()
{
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
        return;
    }
    
    Bullet* pBullet = this;
    UpdatedEvent(this, pBullet);
}
