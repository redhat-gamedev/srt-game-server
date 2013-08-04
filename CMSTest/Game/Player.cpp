//
//  Player.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Player.h"
#include "Bullet.h"
#include "BulletFactory.h"
#include "B2DBulletFactory.h"
#include "B2DWorld.h"
#include "AB2DEntity.h"
#include "World.h"
#include "Timer.h"
#include "B2DPod.h"
#include "Poco/Delegate.h"
#include "../Proto/box2d.pb.h"
#include "../Shared/MakeT.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include <iostream>
#include <iomanip>
#include <assert.h>

Poco::BasicEvent<Player*&>      Player::UpdatedEvent;
uint32_t                        Player::s_ui32Count = 1;


// Constructor(s)
Player::Player(_Dependencies& theDependencies) :
    m_pBulletTimer(new Rock2D::Timer(500)),
    AEntity(theDependencies.UUID,
        (uint64_t)MakeT<uint64_t>((uint32_t)AEntity::POD, s_ui32Count), theDependencies.pB2DEntity)
{
    assert(m_pB2DEntity);
    
    //cout << hex << "Bullet::Bullet() " << m_ui64Tag << endl;
    
    ++s_ui32Count;
    
    m_pB2DEntity->SetParentEntity(this);
    
    FactoryT<DualStickRawInputCommand, RawInputCommand::_RawInputDependencies>&      theDualStickRawInputCommandFactory = FactoryT<DualStickRawInputCommand, RawInputCommand::_RawInputDependencies>::Instance();
    
    theDualStickRawInputCommandFactory.CreatedEvent += Poco::Delegate<Player, DualStickRawInputCommand*&>(this, &Player::HandleDualStickRawInputCommandFactoryCreatedEvent);
    theDualStickRawInputCommandFactory.DestroyedEvent += Poco::Delegate<Player, DualStickRawInputCommand*&>(this, &Player::HandleDualStickRawInputCommandFactoryDestroyedEvent);
}
// Destructor(s)
Player::~Player()
{
    FactoryT<DualStickRawInputCommand, RawInputCommand::_RawInputDependencies>&      theDualStickRawInputCommandFactory = FactoryT<DualStickRawInputCommand, RawInputCommand::_RawInputDependencies>::Instance();
    
    theDualStickRawInputCommandFactory.DestroyedEvent -= Poco::Delegate<Player, DualStickRawInputCommand*&>(this, &Player::HandleDualStickRawInputCommandFactoryDestroyedEvent);
    theDualStickRawInputCommandFactory.CreatedEvent -= Poco::Delegate<Player, DualStickRawInputCommand*&>(this, &Player::HandleDualStickRawInputCommandFactoryCreatedEvent);

    BulletFactory& aBulletFactory = BulletFactory::Instance();
    
    //cout << hex << "Player::~Player() " << m_ui64Tag << endl;
    
    //--s_ui32Count;

    m_BulletQueue.lock();
    Bullet* pBullet = NULL;
    while (!(m_BulletQueue.empty()))
    {
        pBullet = m_BulletQueue.pop();
        aBulletFactory.Destroy(pBullet);
    }
    m_BulletQueue.unlock();
    
    delete m_pBulletTimer;
    m_pBulletTimer = NULL;
    
    //EventPublisher.DestroyedEvent(this, AEntity::POD);
}

// Method(s)
void Player::Update()
{
    assert(m_pB2DEntity);
    assert(m_pBulletTimer);

    B2DBulletFactory& aB2DBulletFactory = B2DBulletFactory::Instance();
    BulletFactory& aBulletFactory = BulletFactory::Instance();

    m_b2v2MoveQueue.lock();
    std::vector<b2Vec2> vecb2v2Move = m_b2v2MoveQueue.toArray();
    m_b2v2MoveQueue.clear();
    m_b2v2MoveQueue.unlock();
    
    for (int i = 0; i < vecb2v2Move.size(); ++i)
    {
        m_pB2DEntity->Move(vecb2v2Move[i].x, vecb2v2Move[i].y);
    }
    
    m_b2v2ShootQueue.lock();
    std::vector<b2Vec2> vecb2v2Shoot = m_b2v2ShootQueue.toArray();
    m_b2v2ShootQueue.clear();
    m_b2v2ShootQueue.unlock();

    for (int i = 0; i < vecb2v2Shoot.size(); ++i)
    {
        if (m_pBulletTimer->Status() == Rock2D::Timer::EXPIRED)
        {
            m_pBulletTimer->Restart();
            
            B2DBullet::_Dependencies aB2DBulletDependencies(m_pB2DEntity->GetPosition(), m_pB2DEntity->GetLinearVelocity());
            B2DBullet* pB2DBullet = aB2DBulletFactory.Create(aB2DBulletDependencies);
            
            Bullet::_Dependencies aBulletDependencies(m_strUUID, pB2DBullet);
            Bullet* pBullet = aBulletFactory.Create(aBulletDependencies);
            
            pBullet->Fire(vecb2v2Shoot[i]);
            m_BulletQueue.lock();
            m_BulletQueue.push(pBullet);
            m_BulletQueue.unlock();
        }
    }
    
    Rock2D::Timer::Update();
    m_pB2DEntity->Update();

    Player* pPlayer = this;
    UpdatedEvent(this, pPlayer);
    
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
        aBulletFactory.Destroy(pBullet);
    }
    m_BulletQueue.unlock();
}

void Player::HandleDualStickRawInputCommandFactoryCreatedEvent(const void* pSender, DualStickRawInputCommand*& pDualStickRawInputCommand)
{
    assert(pDualStickRawInputCommand);
    
    pDualStickRawInputCommand->ExecutedEvent += Poco::Delegate<Player, const std::string&>(this, &Player::HandleDualStickRawInputCommandExecutedEvent);
}

void Player::HandleDualStickRawInputCommandFactoryDestroyedEvent(const void* pSender, DualStickRawInputCommand*& pDualStickRawInputCommand)
{
    assert(pDualStickRawInputCommand);
    
    pDualStickRawInputCommand->ExecutedEvent -= Poco::Delegate<Player, const std::string&>(this, &Player::HandleDualStickRawInputCommandExecutedEvent);
}

void Player::HandleDualStickRawInputCommandExecutedEvent(const void* pSender, const std::string& strUUID)
{
    if (m_strUUID != strUUID)
    {
        return;
    }
    
    const DualStickRawInputCommand* pDualStickInputCommand = static_cast<const DualStickRawInputCommand*>(pSender);
    assert(pDualStickInputCommand);
    
    if (((pDualStickInputCommand->m_b2v2Move.x > 0.0f) ||
        (pDualStickInputCommand->m_b2v2Move.x < 0.0f)) ||
        ((pDualStickInputCommand->m_b2v2Move.y > 0.0f) ||
         (pDualStickInputCommand->m_b2v2Move.y < 0.0f)))
    {
        m_b2v2MoveQueue.lock();
        m_b2v2MoveQueue.push(b2Vec2(pDualStickInputCommand->m_b2v2Move.x, pDualStickInputCommand->m_b2v2Move.y));
        m_b2v2MoveQueue.unlock();
    }
    
    if (((pDualStickInputCommand->m_b2v2Shoot.x > 0.0f)  ||
         (pDualStickInputCommand->m_b2v2Shoot.x < 0.0f)) ||
        ((pDualStickInputCommand->m_b2v2Shoot.y > 0.0f)  ||
         (pDualStickInputCommand->m_b2v2Shoot.y < 0.0f)))
    {
        m_b2v2ShootQueue.lock();
        m_b2v2ShootQueue.push(b2Vec2(pDualStickInputCommand->m_b2v2Shoot.x, pDualStickInputCommand->m_b2v2Shoot.y));
        m_b2v2ShootQueue.unlock();
    }
}
