//
//  Messenger.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger.h"
#include "Messenger_Producer.h"
#include "../Game/EntityData.h"
#include "../Game/Player.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "Poco/Delegate.h"
#include "Poco/FunctionDelegate.h"
#include <decaf/lang/Thread.h>
#include <string>
#include <assert.h>

Messenger::_Producer            Messenger::Producer;
const std::string               Messenger::BrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";


// Constructor(s)
Messenger::Messenger()
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
    std::string     strDestinationURI = "WORLD.SIMULATION";
    
    Producer.Setup(strBrokerURI, strDestinationURI);
    
    Player::EventPublisher.CreatedEvent += Poco::FunctionDelegate<const EntityData&>(&Messenger::OnPlayerCreated);
    Player::EventPublisher.DestroyedEvent += Poco::FunctionDelegate<const EntityData&>(&Messenger::OnPlayerDestroyed);
}

void Messenger::Teardown()
{
    Player::EventPublisher.DestroyedEvent -= Poco::FunctionDelegate<const EntityData&>(&Messenger::OnPlayerDestroyed);
    Player::EventPublisher.CreatedEvent -= Poco::FunctionDelegate<const EntityData&>(&Messenger::OnPlayerCreated);

    Producer.Teardown();
}

void Messenger::Send()
{
    Producer.SendUpdates();
}


// Player Event response
void Messenger::OnPlayerCreated(const void* pSender, const EntityData& anEntityData)
{
    using namespace gameevent;
    
    static std::string strPBBuffer = "";

    GameEvent* pGameEvent = new GameEvent();
    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
    assert(NULL != pEntityGameEvent);

    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_CREATE);
    pEntityGameEvent->set_uuid(anEntityData.UUID);
    pEntityGameEvent->set_entitytag(anEntityData.Tag);

    Producer.Enqueue(pGameEvent);
}

void Messenger::OnPlayerDestroyed(const void* pSender, const EntityData& anEntityData)
{
    using namespace gameevent;
    
    static std::string strPBBuffer = "";
    
    GameEvent* pGameEvent = new GameEvent();
    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
    assert(NULL != pEntityGameEvent);
    
    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_DESTROY);
    pEntityGameEvent->set_uuid(anEntityData.UUID);
    pEntityGameEvent->set_entitytag(anEntityData.Tag);
    
    Producer.Enqueue(pGameEvent);
}