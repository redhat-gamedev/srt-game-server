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
#include "../Game/Bullet.h"
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
    
    s_pMessengerSerialDispatchQueue = new xdispatch::queue("messenger");
    
    // World Simulation
    //Producer.Setup(strBrokerURI, strWorldSimulationDestinationURI);
    
    // Game Event
    GameEventProducer.Setup(strBrokerURI, strGameEventOutDestinationURI);
    Consumer.Setup(strBrokerURI, strGameEventInDestinationURI);
    
    Player::EventPublisher.CreatedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityCreated);
    Player::EventPublisher.UpdatedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityUpdated);
    Player::EventPublisher.DestroyedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityDestroyed);
    
    //Bullet::EventPublisher.CreatedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityCreated);
    Bullet::EventPublisher.UpdatedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityUpdated);
    //Bullet::EventPublisher.DestroyedEvent += Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityDestroyed);

    Bullet::Factory().CreatedEvent += Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletCreatedEvent);
    Bullet::Factory().DestroyedEvent += Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletDestroyedEvent);
    
//    std::cout << "Starting " << strThreadName << std::endl;
//    s_pThread = new decaf::lang::Thread(this, strThreadName);
//    s_pThread->start();
}

void Messenger::Teardown()
{
//    delete s_pThread;
//    s_pThread = NULL;

    //Bullet::EventPublisher.DestroyedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityDestroyed);
    Bullet::EventPublisher.UpdatedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityUpdated);
    //Bullet::EventPublisher.CreatedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityCreated);

    Bullet::Factory().DestroyedEvent -= Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletDestroyedEvent);
    Bullet::Factory().CreatedEvent -= Poco::FunctionDelegate<Bullet*&>(&Messenger::HandleBulletCreatedEvent);

    Player::EventPublisher.DestroyedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityDestroyed);
    Player::EventPublisher.UpdatedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityUpdated);
    Player::EventPublisher.CreatedEvent -= Poco::FunctionDelegate<const AEntity::EType&>(&Messenger::OnEntityCreated);

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

// Player Event response
void Messenger::OnEntityCreated(const void* pSender, const AEntity::EType& anEntityType)
{
    using namespace gameevent;
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        const AEntity* pEntity = static_cast<const AEntity*>(pSender);
        
        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        //GameEvent* pGameEvent = new GameEvent();
        pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
        
        EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_CREATE);

        AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);
        GameEventProducer.Enqueue(pGameEvent);
    });
}

void Messenger::OnEntityUpdated(const void* pSender, const AEntity::EType& anEntityType)
{
    using namespace std;
    using namespace gameevent;
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        const AEntity* pEntity = static_cast<const AEntity*>(pSender);

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
    });
}

void Messenger::OnEntityDestroyed(const void* pSender, const AEntity::EType& anEntityType)
{
    using namespace gameevent;

    s_pMessengerSerialDispatchQueue->sync([=]
    {
        const AEntity* pEntity = static_cast<const AEntity*>(pSender);
        
        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        //GameEvent* pGameEvent = new GameEvent();
        pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
        
        EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_DESTROY);

        AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);
        
        //Producer.Enqueue(pGameEvent);
        //std::cout << "OnEntityDestroyed message " << aGameEvent.DebugString() << std::endl;
        GameEventProducer.Enqueue(pGameEvent);
    });
}

void Messenger::HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet)
{
    using namespace gameevent;
    
    assert(pBullet);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        const AEntity* pEntity = static_cast<const AEntity*>(pBullet);

        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        //GameEvent* pGameEvent = new GameEvent();
        pGameEvent->set_type(GameEvent_GameEventType_ENTITY);

        EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_CREATE);

        AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);
        GameEventProducer.Enqueue(pGameEvent);
    });
}

void Messenger::HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet)
{
    using namespace gameevent;
 
    assert(pBullet);
    
    s_pMessengerSerialDispatchQueue->sync([=]
    {
        const AEntity* pEntity = static_cast<const AEntity*>(pBullet);

        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        //GameEvent* pGameEvent = new GameEvent();
        pGameEvent->set_type(GameEvent_GameEventType_ENTITY);

        EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_DESTROY);

        AEntity::Serializer.Serialize(pEntity, pEntityGameEvent);

        //Producer.Enqueue(pGameEvent);
        //std::cout << "OnEntityDestroyed message " << aGameEvent.DebugString() << std::endl;
        GameEventProducer.Enqueue(pGameEvent);
    });
}