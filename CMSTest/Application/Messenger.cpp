//
//  Messenger.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger.h"
#include "Messenger_Producer.h"
#include "Messenger_Consumer.h"
#include "../Game/AEntity.h"
#include "../Game/Player.h"
#include "../Game/PodFactory.h"
#include "../Game/Bullet.h"
#include "../Game/BulletFactory.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "Poco/Delegate.h"
#include "Poco/FunctionDelegate.h"
//#include <decaf/lang/Thread.h>
#include <string>
#include <iostream>
//#include <bitset>
#include <assert.h>

//Messenger::_Producer            Messenger::Producer;
Messenger::_Producer            Messenger::GameEventProducer;
Messenger::_Consumer            Messenger::Consumer;
const std::string               Messenger::BrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
xdispatch::queue*               Messenger::s_pMessengerSerialDispatchQueue = NULL;

// Constructor(s)
Messenger::Messenger()// :
    //s_pThread(NULL)
{

}

// Destructor(s)
Messenger::~Messenger()
{

}

// Class function(s)
void Messenger::Setup()
{
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    //std::string     strWorldSimulationDestinationURI = "WORLD.SIMULATION";
    std::string     strGameEventInDestinationURI = "GAME.EVENT.IN";
    std::string     strGameEventOutDestinationURI = "GAME.EVENT.OUT";
    std::string     strThreadName = "MessengerThread";

    PodFactory&  aPodFactory = PodFactory::Instance();
    BulletFactory&  aBulletFactory = BulletFactory::Instance();

    
    s_pMessengerSerialDispatchQueue = new xdispatch::queue("messenger");
    
    // World Simulation
    //Producer.Setup(strBrokerURI, strWorldSimulationDestinationURI);
    
    // Game Event
    GameEventProducer.Setup(strBrokerURI, strGameEventOutDestinationURI);
    Consumer.Setup(strBrokerURI, strGameEventInDestinationURI);
    
    aPodFactory.CreatedEvent += Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodCreatedEvent);
    Player::UpdatedEvent += Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodUpdatedEvent);
    aPodFactory.DestroyedEvent += Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodDestroyedEvent);
    
    aBulletFactory.CreatedEvent += Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletCreatedEvent);
    Bullet::UpdatedEvent += Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletUpdatedEvent);
    aBulletFactory.DestroyedEvent += Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletDestroyedEvent);
    
//    std::cout << "Starting " << strThreadName << std::endl;
//    s_pThread = new decaf::lang::Thread(this, strThreadName);
//    s_pThread->start();
}

void Messenger::Teardown()
{
    PodFactory&  aPodFactory = PodFactory::Instance();    
    BulletFactory&  aBulletFactory = BulletFactory::Instance();
    
//    delete s_pThread;
//    s_pThread = NULL;

    aBulletFactory.DestroyedEvent -= Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletDestroyedEvent);
    Bullet::UpdatedEvent -= Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletUpdatedEvent);
    aBulletFactory.CreatedEvent -= Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletCreatedEvent);

    aPodFactory.DestroyedEvent -= Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodDestroyedEvent);
    Player::UpdatedEvent -= Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodUpdatedEvent);
    aPodFactory.CreatedEvent -= Poco::FunctionDelegate<Player*&>(&Messenger::HandlePodCreatedEvent);
    
    GameEventProducer.Teardown();
    Consumer.Teardown();
    //Producer.Teardown();
    
    delete s_pMessengerSerialDispatchQueue;
    s_pMessengerSerialDispatchQueue = NULL;
}

//void Messenger::Send()
//{
//    GameEventProducer.SendUpdates();
//    Producer.SendUpdates();
//}

//void Messenger::run()
//{
//    Producer.SendUpdates();
//    GameEventProducer.SendUpdates();
//}

void Messenger::SendUpdates()
{
    //Producer.SendUpdates();
    GameEventProducer.SendUpdates();
}

// Helper(s)
void Messenger::EnqueueEntityCreatedEvent(AEntity* pEntity)
{
    using namespace gameevent;

    GameEvent aGameEvent;
    GameEvent* pGameEvent = aGameEvent.New();
    //GameEvent* pGameEvent = new GameEvent();
    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
    
    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
    assert(NULL != pEntityGameEvent);
    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_CREATE);
    
    AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);
    GameEventProducer.Enqueue(pGameEvent);
}

void Messenger::EnqueueEntityUpdatedEvent(AEntity* pEntity)
{
    using namespace std;
    using namespace gameevent;

    GameEvent aGameEvent;
    GameEvent* pGameEvent = aGameEvent.New();
    //GameEvent* pGameEvent = new GameEvent();
    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
    
    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
    assert(NULL != pEntityGameEvent);
    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_UPDATE);
    
    AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);
    //        if (pEntityGameEvent)
    //        {
    //            uint64_t ui64Tag = pEntityGameEvent->entitytag();
    //            bitset<sizeof(uint64_t)*8>    aBitSet(ui64Tag);
    //            //cout << hex << pEntityGameEvent->entitytag() << endl;
    //            cout << aBitSet << endl;
    //        }
    GameEventProducer.Enqueue(pGameEvent);
}

void Messenger::EnqueueEntityDestroyedEvent(AEntity* pEntity)
{
    using namespace gameevent;

    GameEvent aGameEvent;
    GameEvent* pGameEvent = aGameEvent.New();
    //GameEvent* pGameEvent = new GameEvent();
    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
    
    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
    assert(NULL != pEntityGameEvent);
    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_DESTROY);
    
    AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);

    //std::cout << "OnEntityDestroyed message " << aGameEvent.DebugString() << std::endl;
    GameEventProducer.Enqueue(pGameEvent);
}


// Bullet Event response
void Messenger::HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet)
{
    assert(pBullet);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pBullet);
        EnqueueEntityCreatedEvent(pEntity);
    });
}

void Messenger::HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet)
{
    assert(pBullet);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pBullet);
        EnqueueEntityDestroyedEvent(pEntity);
    });
}

void Messenger::HandleBulletUpdatedEvent(const void* pSender, Bullet*& pBullet)
{
    assert(pBullet);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pBullet);
        EnqueueEntityUpdatedEvent(pEntity);
    });
}

// Player Event response
void Messenger::HandlePodCreatedEvent(const void* pSender, Player*& pPlayer)
{
    assert(pPlayer);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pPlayer);
        EnqueueEntityCreatedEvent(pEntity);
    });
}

void Messenger::HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer)
{
    assert(pPlayer);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pPlayer);
        EnqueueEntityDestroyedEvent(pEntity);
    });
}

void Messenger::HandlePodUpdatedEvent(const void* pSender, Player*& pPlayer)
{
    assert(pPlayer);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        AEntity* pEntity = static_cast<AEntity*>(pPlayer);
        EnqueueEntityUpdatedEvent(pEntity);
    });
}