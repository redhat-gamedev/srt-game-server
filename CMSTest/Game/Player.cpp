//
//  Player.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Player.h"
#include "Bullet.h"
#include "B2DWorld.h"
#include "B2DWorld_BuildT.h"
#include "World.h"
#include "Timer.h"
#include "EntityData.h"
#include "B2DPod.h"
#include "Input.h"
#include "../Proto/box2d.pb.h"
#include "Poco/Delegate.h"
#include "../Shared/MakeT.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <assert.h>

Player::_EventPublisher     Player::EventPublisher;
uint32_t                    Player::s_ui32Count = 1;


// Constructor(s)
Player::Player(const std::string& strUUID) :
    m_pBulletTimer(NULL),
    m_pB2DPod(NULL),
    AEntity(strUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::POD, s_ui32Count))
{
    ++s_ui32Count;
    
    //FireCreatedEvent(m_strUUID);
    CreatePod();
    
    EventPublisher.CreatedEvent(this, EntityData(m_ui64Tag, m_strUUID));
}

// Destructor(s)
Player::~Player()
{
    //FireDestroyedEvent(m_strUUID);
    EventPublisher.DestroyedEvent(this, EntityData(m_ui64Tag, m_strUUID));

    --s_ui32Count;
    
    DestroyPod();
}

// Method(s)
void Player::Update()
{
    assert(m_pB2DPod);
    
    Rock2D::Timer::Update();
    m_pB2DPod->Update();
    
    Bullet* pBullet = NULL;
    m_BulletQueue.lock();
    std::list<Bullet*>      aBulletToRemoveList;
    std::list<Bullet*>      aBulletToAddList;
    while (!m_BulletQueue.empty())
    {
        pBullet = m_BulletQueue.pop();
        if (pBullet->m_pLifeTimer->Status() == Rock2D::Timer::EXPIRED)
        {
            aBulletToRemoveList.push_front(pBullet);
        }
        else
        {
            aBulletToAddList.push_front(pBullet);
        }
    }
    while (!aBulletToAddList.empty())
    {
        pBullet = aBulletToAddList.front();
        aBulletToAddList.pop_front();
        m_BulletQueue.push(pBullet);
    }
    m_BulletQueue.unlock();
    
    while (!aBulletToRemoveList.empty())
    {
        pBullet = aBulletToRemoveList.front();
        aBulletToRemoveList.pop_front();
        delete pBullet;
        pBullet = NULL;
    }
}

void Player::CreatePod()
{
    m_pBulletTimer = new Rock2D::Timer(1000);
    m_pB2DPod = new B2DPod(new EntityData(m_ui64Tag, m_strUUID));

    Input::EventPublisher.DualStickEvent += Poco::Delegate<Player, DualStick::PbDualStick>(this, &Player::OnInputDualStick);
}

void Player::DestroyPod()
{
    Input::EventPublisher.DualStickEvent -= Poco::Delegate<Player, DualStick::PbDualStick>(this, &Player::OnInputDualStick);
    
    m_BulletQueue.lock();
    Bullet* pBullet = NULL;
    while (!(m_BulletQueue.empty()))
    {
        pBullet = m_BulletQueue.pop();
        delete pBullet;
        pBullet = NULL;
    }
    m_BulletQueue.unlock();
    
    delete m_pB2DPod;
    m_pB2DPod = NULL;
    
    delete m_pBulletTimer;
    m_pBulletTimer = NULL;    
}

//// Event Firing Method(s)
//void Player::FireCreatedEvent(const EntityData& anEntityData)
//{
//    EventPublisher.CreatedEvent(this, anEntityData);
//}
//
//void Player::FireDestroyedEvent(const EntityData& anEntityData)
//{
//    EventPublisher.DestroyedEvent(this, anEntityData);
//}

// Input Event response
void Player::OnInputDualStick(const void* pSender, DualStick::PbDualStick& aPbDualStick)
{
    assert(m_pB2DPod);
    assert(m_pBulletTimer);

    const box2d::PbVec2& pbv2Move = aPbDualStick.pbv2move();
    const box2d::PbVec2& pbv2Shoot = aPbDualStick.pbv2shoot();
    const std::string& strUUID = aPbDualStick.uuid();

    if (strUUID != m_strUUID)
    {
        return;
    }
    
    b2Vec2 b2v2Shoot;
    Bullet* pBullet = NULL;
    
    b2v2Shoot.x = pbv2Shoot.x();
    b2v2Shoot.y = pbv2Shoot.y();
    
    m_pB2DPod->Move(pbv2Move.x(), pbv2Move.y());
    
    if (((b2v2Shoot.x < 0.0f) || (b2v2Shoot.x > 0.0f)) ||
        ((b2v2Shoot.y < 0.0f) || (b2v2Shoot.y > 0.0f)))
    {
        if (m_pBulletTimer->Status() == Rock2D::Timer::EXPIRED)
        {
            pBullet = new Bullet(m_strUUID, m_pB2DPod->GetPosition(), b2v2Shoot);
            m_BulletQueue.lock();
            m_BulletQueue.push(pBullet);
            m_BulletQueue.unlock();
            m_pBulletTimer->Restart();
        }
    }
}
