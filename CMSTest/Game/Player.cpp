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
//#include "Input.h"
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
    
    //Input::EventPublisher.DualStickEvent += Poco::Delegate<Player, DualStick::PbDualStick>(this, &Player::OnInputDualStick);
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

    //Input::EventPublisher.DualStickEvent -= Poco::Delegate<Player, DualStick::PbDualStick>(this, &Player::OnInputDualStick);
    
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
#if 0
//    m_PbDualStickQueue.lock();
//    std::vector<DualStick::PbDualStick> vecPbDualStick = m_PbDualStickQueue.toArray();
//    m_PbDualStickQueue.clear();
//    m_PbDualStickQueue.unlock();
    
    //while (!aPbDualStickQueueSwap.empty())
    
    //for (int i = 0; i < vecPbDualStick.size(); ++i)
    {
        //DualStick::PbDualStick aPbDualStick = aPbDualStickQueueSwap.pop();
        //DualStick::PbDualStick aPbDualStick = vecPbDualStick[i];
        //const box2d::PbVec2& pbv2Move = aPbDualStick.pbv2move();
        //const box2d::PbVec2& pbv2Shoot = aPbDualStick.pbv2shoot();
//        const box2d::PbVec2& pbv2Move = aPbDualStick.pbv2move();
//        const box2d::PbVec2& pbv2Shoot = aPbDualStick.pbv2shoot();
        const std::string& strUUID = "";//aPbDualStick.uuid();

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
                m_pBulletTimer->Restart();
                
                B2DBullet::_Dependencies aB2DBulletDependencies(m_pB2DEntity->GetPosition(), m_pB2DEntity->GetLinearVelocity());
                B2DBullet* pB2DBullet = aB2DBulletFactory.Create(aB2DBulletDependencies);
                
                Bullet::_Dependencies aBulletDependencies(m_strUUID, pB2DBullet);
                Bullet* pBullet = aBulletFactory.Create(aBulletDependencies);
                
                pBullet->Fire(b2v2Shoot);
                m_BulletQueue.lock();
                m_BulletQueue.push(pBullet);
                m_BulletQueue.unlock();
            }
        }
    }
#endif
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

// Input Event response
//void Player::OnInputDualStick(const void* pSender, DualStick::PbDualStick& aPbDualStick)
//{
//    m_PbDualStickQueue.lock();
//    m_PbDualStickQueue.push(aPbDualStick);
//    m_PbDualStickQueue.unlock();
//}

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
    //GameEventBuffer* pGameEvent = CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType_JOIN, strUUID);
    //Enqueue(pGameEvent);
    int i = 0;
    ++i;
}
