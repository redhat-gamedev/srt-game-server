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
    m_pBulletTimer(new Rock2D::Timer(250)),
    AEntity(strUUID,
            (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::POD, s_ui32Count),
            new B2DPod(this))
{
    ++s_ui32Count;
    
    Input::EventPublisher.DualStickEvent += Poco::Delegate<Player, DualStick::PbDualStick>(this, &Player::OnInputDualStick);

    EventPublisher.CreatedEvent(this, AEntity::POD);
}

// Destructor(s)
Player::~Player()
{
    //--s_ui32Count;

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
    
    delete m_pBulletTimer;
    m_pBulletTimer = NULL;
    
    EventPublisher.DestroyedEvent(this, AEntity::POD);
}

// Method(s)
void Player::Update()
{
    assert(m_pB2DEntity);
    assert(m_pBulletTimer);

    m_PbDualStickQueue.lock();
//    decaf::util::StlQueue<DualStick::PbDualStick>   aPbDualStickQueueSwap = m_PbDualStickQueue;
    std::vector<DualStick::PbDualStick> vecPbDualStick = m_PbDualStickQueue.toArray();
    m_PbDualStickQueue.clear();
    m_PbDualStickQueue.unlock();
    
    //while (!aPbDualStickQueueSwap.empty())
    for (int i = 0; i < vecPbDualStick.size(); ++i)
    {
        //DualStick::PbDualStick aPbDualStick = aPbDualStickQueueSwap.pop();
        DualStick::PbDualStick aPbDualStick = vecPbDualStick[i];
        const box2d::PbVec2& pbv2Move = aPbDualStick.pbv2move();
        const box2d::PbVec2& pbv2Shoot = aPbDualStick.pbv2shoot();
        const std::string& strUUID = aPbDualStick.uuid();

        if (strUUID != m_strUUID)
        {
            return;
        }
    
        b2Vec2 b2v2Shoot;
        b2v2Shoot.x = pbv2Shoot.x();
        b2v2Shoot.y = pbv2Shoot.y();

        m_pB2DEntity->Move(pbv2Move.x(), pbv2Move.y());

        if (((b2v2Shoot.x < 0.0f) || (b2v2Shoot.x > 0.0f)) ||
            ((b2v2Shoot.y < 0.0f) || (b2v2Shoot.y > 0.0f)))
        {
            if (m_pBulletTimer->Status() == Rock2D::Timer::EXPIRED)
            {
                //b2v2Shoot.Normalize();
                //b2v2Shoot *= m_pB2DEntity->GetLinearVelocity().Length();

                m_pBulletTimer->Restart();
                Bullet* pBullet = NULL;
                pBullet = new Bullet(m_strUUID, m_pB2DEntity->GetPosition(), m_pB2DEntity->GetLinearVelocity(), b2v2Shoot);
                m_BulletQueue.lock();
                m_BulletQueue.push(pBullet);
                m_BulletQueue.unlock();
            }
        }
    }

    Rock2D::Timer::Update();
    m_pB2DEntity->Update();
    

    std::list<Bullet*>      aBulletToRemoveList;
    std::list<Bullet*>      aBulletToAddList;
    m_BulletQueue.lock();
    while (!m_BulletQueue.empty())
    {
        Bullet* pBullet = NULL;
        pBullet = m_BulletQueue.pop();
        pBullet->Update();
        if (!pBullet->Alive())
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
        Bullet* pBullet = NULL;
        pBullet = aBulletToAddList.front();
        aBulletToAddList.pop_front();
        m_BulletQueue.push(pBullet);
    }
    while (!aBulletToRemoveList.empty())
    {
        Bullet* pBullet = NULL;
        pBullet = aBulletToRemoveList.front();
        aBulletToRemoveList.pop_front();
        delete pBullet;
        pBullet = NULL;
    }
    m_BulletQueue.unlock();
}

// Input Event response
void Player::OnInputDualStick(const void* pSender, DualStick::PbDualStick& aPbDualStick)
{
    m_PbDualStickQueue.lock();
    m_PbDualStickQueue.push(aPbDualStick);
    m_PbDualStickQueue.unlock();
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

