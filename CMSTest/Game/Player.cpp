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
#include "UserData.h"
#include "B2DPod.h"
#include "../Shared/MakeT.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <assert.h>

Player::_Publisher          Player::Publisher;
uint32_t                    Player::s_ui32Count = 1;


// Constructor(s)
/*
 Player::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 Player::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void Player::_Publisher::OnPlayerCreated(const std::string& strUUID)
{
    xdispatch::global_queue().async([=]
    {
        ICallbacks* pObjToCallback = NULL;
        
        //m_listSubscribersSwap = m_listSubscribers;
        Clone(m_listSubscribersSwap);
        while(!m_listSubscribersSwap.empty())
        {
            pObjToCallback = m_listSubscribersSwap.front();
            m_listSubscribersSwap.pop_front();
            assert(pObjToCallback);
            pObjToCallback->OnPlayerCreated(strUUID);
        }
    });
}

void Player::_Publisher::OnPlayerDestroyed(const std::string& strUUID)
{
    xdispatch::global_queue().async([=]
    {
        ICallbacks* pObjToCallback = NULL;
        
        //m_listSubscribersSwap = m_listSubscribers;
        Clone(m_listSubscribersSwap);
        while(!m_listSubscribersSwap.empty())
        {
            pObjToCallback = m_listSubscribersSwap.front();
            m_listSubscribersSwap.pop_front();
            assert(pObjToCallback);
            pObjToCallback->OnPlayerDestroyed(strUUID);
        }
    });
}


// Constructor(s)
Player::Player(const std::string& strUUID) :
    m_pBulletTimer(NULL),
    m_pB2DPod(NULL),
    AEntity(strUUID, (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::POD, s_ui32Count))
{
    ++s_ui32Count;
    
    m_pBulletTimer = new Rock2D::Timer(1000);
    m_pB2DPod = new B2DPod(new UserData(m_ui64Tag, m_strUUID));
    
    Publisher.OnPlayerCreated(m_strUUID);
    
    Input::Publisher.Attach(this);
}

// Destructor(s)
Player::~Player()
{
    --s_ui32Count;
    
    Input::Publisher.Detach(this);

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
    
    Publisher.OnPlayerDestroyed(m_strUUID);
    
    delete m_pBulletTimer;
    m_pBulletTimer = NULL;
}

// Method(s)
void Player::Update()
{
    assert(m_pB2DPod);
    
    Rock2D::Timer::Update();
    m_pB2DPod->Update();
    
    Bullet* pBullet = NULL;
    m_b2v2ShootQueue.lock();
    std::vector<b2Vec2> aShootVector = m_b2v2ShootQueue.toArray();
    m_b2v2ShootQueue.clear();
    m_b2v2ShootQueue.unlock();

    for (int i = 0; i < aShootVector.size(); ++i)
    {
        if (m_pBulletTimer->Status() == Rock2D::Timer::EXPIRED)
        {
            pBullet = new Bullet(m_strUUID, m_pB2DPod->GetPosition(), aShootVector[i]);
            m_BulletQueue.lock();
            m_BulletQueue.push(pBullet);
            m_BulletQueue.unlock();
            m_pBulletTimer->Restart();
        }
    }
    aShootVector.clear();

//    m_BulletQueue.lock();
//    std::vector<Bullet*>    aBulletVector = m_BulletQueue.toArray();
//    m_BulletQueue.unlock();
//    std::list<Bullet*>      aBulletToRemoveList;
//    for(int j = 0; j < aBulletVector.size(); ++j)
//    {
//        pBullet = aBulletVector[j];
//        if (pBullet->m_pLifeTimer->Status() == Rock2D::Timer::EXPIRED)
//        {
//            aBulletToRemoveList.push_front(pBullet);
//        }
//    }
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

// Input::ICallbacks implementation
void Player::OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot)
{
    assert(m_pB2DPod);
    
    if (strUUID != m_strUUID)
    {
        return;
    }

    b2Vec2 b2v2Shoot;
    
    b2v2Shoot.x = pbv2Shoot.x();
    b2v2Shoot.y = pbv2Shoot.y();

    m_pB2DPod->Move(pbv2Move.x(), pbv2Move.y());
    
    if (((b2v2Shoot.x < 0.0f) || (b2v2Shoot.x > 0.0f)) ||
        ((b2v2Shoot.y < 0.0f) || (b2v2Shoot.y > 0.0f)))
    {
        m_b2v2ShootQueue.lock();
        m_b2v2ShootQueue.push(b2v2Shoot);
        m_b2v2ShootQueue.unlock();
    }
}
