//
//  EventDispatcher.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "EventDispatcher.h"
#include "AEntity.h"
#include "Player.h"
#include "PodFactory.h"
#include "Bullet.h"
#include "BulletFactory.h"
//#include "EntityGameEventFactory.h"
//#include "../proto/EntityGameEventBuffer.pb.h"
#include "Poco/Delegate.h"
#include <assert.h>

using namespace usx::geofactions;
using namespace google::protobuf;


// Constructor
EventDispatcher::
_Dependencies::
_Dependencies(PodFactory& aPodFactory, BulletFactory& aBulletFactory, FactoryT<usx::geofactions::GameEventBuffer, EntityGameEvent_Dependencies>& anEntityGameEventFactory) :
    m_aPodFactory(aPodFactory),
    m_aBulletFactory(aBulletFactory),
    m_anEntityGameEventFactory(anEntityGameEventFactory)
{
}

// Destructor
EventDispatcher::
_Dependencies::
~_Dependencies()
{
    
}

// Constructor(s)
EventDispatcher::EventDispatcher(_Dependencies* pDependencies) :
    m_anEntityGameEventFactory(pDependencies->m_anEntityGameEventFactory)

{
    assert(pDependencies);
    
   // Pod event observation
    pDependencies->m_aPodFactory.CreatedEvent += Poco::Delegate<EventDispatcher, Player*&>(this, &EventDispatcher::HandlePodCreatedEvent);
    Player::UpdatedEvent += Poco::Delegate<EventDispatcher, Player*&>(this, &EventDispatcher::HandlePodUpdatedEvent);
    pDependencies->m_aPodFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, Player*&>(this, &EventDispatcher::HandlePodDestroyedEvent);
    
    // Bullet event observation
    pDependencies->m_aBulletFactory.CreatedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletCreatedEvent);
    Bullet::UpdatedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletUpdatedEvent);
    pDependencies->m_aBulletFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletDestroyedEvent);
}

// Destructor
EventDispatcher::~EventDispatcher()
{
    
}

// Helper(s)
void EventDispatcher::Enqueue(Message* pMessage)
{
    m_anEventQueue.lock();
    m_anEventQueue.push(pMessage);
    m_anEventQueue.unlock();
}

Message* EventDispatcher::Dequeue()
{
    Message* pMessage = NULL;

    m_anEventQueue.lock();
    pMessage = m_anEventQueue.pop();
    m_anEventQueue.unlock();
    
    return pMessage;
}

GameEventBuffer* EventDispatcher::CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType eEntityGameEvent_EntityGameEventBufferType, AEntity* pEntity)
{
    EntityGameEvent_Dependencies anEntityGameEvent_Dependencies(eEntityGameEvent_EntityGameEventBufferType, pEntity);
    GameEventBuffer* pGameEvent = m_anEntityGameEventFactory.Create(anEntityGameEvent_Dependencies);
    
    return pGameEvent;
}

// Method(s)
// Dispatches all the events it has received to it's listeners
void EventDispatcher::Dispatch()
{
    Message* pMessage = NULL;
    m_anEventQueue.lock();
    while (!m_anEventQueue.empty())
    {
        pMessage = m_anEventQueue.pop();
        EventDispatchedEvent(this, pMessage);
    }
    m_anEventQueue.unlock();
}

// Entity event response
void EventDispatcher::HandlePodCreatedEvent(const void* pSender, Player*& pPlayer)
{
//    AEntity* pEntity = static_cast<AEntity*>(pPlayer);
//    EntityGameEvent_Dependencies anEntityGameEvent_Dependencies(EntityGameEvent_EntityGameEventBufferType_CREATE, pEntity);
//    
//    GameEvent* pGameEvent = m_anEntityGameEventFactory.Create(anEntityGameEvent_Dependencies);
//    Enqueue(pGameEvent);

    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_CREATE, static_cast<AEntity*>(pPlayer));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandlePodUpdatedEvent(const void* pSender, Player*& pPlayer)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_UPDATE, static_cast<AEntity*>(pPlayer));
    Enqueue(pGameEvent);}

void EventDispatcher::HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_DESTROY, static_cast<AEntity*>(pPlayer));
    Enqueue(pGameEvent);}

void EventDispatcher::HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_CREATE, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleBulletUpdatedEvent(const void* pSender, Bullet*& pBullet)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_UPDATE, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_DESTROY, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}
