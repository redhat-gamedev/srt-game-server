//
//  EventDispatcher.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "EventDispatcher.h"
#include "../Game/AEntity.h"
#include "../Game/Pod.h"
#include "../Game/PodFactory.h"
#include "../Game/Bullet.h"
#include "../Game/BulletFactory.h"
#include "../Commands/ACommand.h"
#include "../Commands/SecurityCommand.h"
#include "../Commands/JoinSecurityCommand.h"
#include "../Commands/LeaveSecurityCommand.h"
#include "../Shared/FactoryT.h"
#include "Poco/Delegate.h"
#include <assert.h>

using namespace usx::geofactions;
using namespace google::protobuf;


// Constructor
EventDispatcher::
_Dependencies::
_Dependencies(PodFactory& aPodFactory,
              BulletFactory& aBulletFactory,
              FactoryT<usx::geofactions::GameEventBuffer, EntityGameEvent_Dependencies>& anEntityGameEventFactory,
              FactoryT<usx::geofactions::GameEventBuffer, SecurityGameEvent_Dependencies>& aSecurityGameEventFactory) :
    m_aPodFactory(aPodFactory),
    m_aBulletFactory(aBulletFactory),
    m_anEntityGameEventFactory(anEntityGameEventFactory),
    m_aSecurityGameEventFactory(aSecurityGameEventFactory)
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
    m_aPodFactory(pDependencies->m_aPodFactory),
    m_aBulletFactory(pDependencies->m_aBulletFactory),
    m_anEntityGameEventFactory(pDependencies->m_anEntityGameEventFactory),
    m_aSecurityGameEventFactory(pDependencies->m_aSecurityGameEventFactory)

{
    assert(pDependencies);
    
   // Pod event observation
    m_aPodFactory.CreatedEvent += Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodCreatedEvent);
    Pod::UpdatedEvent += Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodUpdatedEvent);
    m_aPodFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodDestroyedEvent);
    
    // Bullet event observation
    m_aBulletFactory.CreatedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletCreatedEvent);
    Bullet::UpdatedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletUpdatedEvent);
    m_aBulletFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletDestroyedEvent);
    
    
    auto& theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    theJoinSecurityCommandFactory.CreatedEvent += Poco::Delegate<EventDispatcher, JoinSecurityCommand*&>(this, &EventDispatcher::HandleJoinSecurityCommandFactoryCreatedEvent);
    theJoinSecurityCommandFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, JoinSecurityCommand*&>(this, &EventDispatcher::HandleJoinSecurityCommandFactoryDestroyedEvent);
    
    auto& theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    theLeaveSecurityCommandFactory.CreatedEvent += Poco::Delegate<EventDispatcher, LeaveSecurityCommand*&>(this, &EventDispatcher::HandleLeaveSecurityCommandFactoryCreatedEvent);
    theLeaveSecurityCommandFactory.DestroyedEvent += Poco::Delegate<EventDispatcher, LeaveSecurityCommand*&>(this, &EventDispatcher::HandleLeaveSecurityCommandFactoryDestroyedEvent);
}

// Destructor
EventDispatcher::~EventDispatcher()
{
    // Bullet event observation
    m_aBulletFactory.CreatedEvent -= Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletCreatedEvent);
    Bullet::UpdatedEvent -= Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletUpdatedEvent);
    m_aBulletFactory.DestroyedEvent -= Poco::Delegate<EventDispatcher, Bullet*&>(this, &EventDispatcher::HandleBulletDestroyedEvent);
    
    // Pod event observation
    m_aPodFactory.CreatedEvent -= Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodCreatedEvent);
    Pod::UpdatedEvent -= Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodUpdatedEvent);
    m_aPodFactory.DestroyedEvent -= Poco::Delegate<EventDispatcher, Pod*&>(this, &EventDispatcher::HandlePodDestroyedEvent);
    
    auto& theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    theJoinSecurityCommandFactory.CreatedEvent -= Poco::Delegate<EventDispatcher, JoinSecurityCommand*&>(this, &EventDispatcher::HandleJoinSecurityCommandFactoryCreatedEvent);
    theJoinSecurityCommandFactory.DestroyedEvent -= Poco::Delegate<EventDispatcher, JoinSecurityCommand*&>(this, &EventDispatcher::HandleJoinSecurityCommandFactoryDestroyedEvent);
    
    auto& theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    theLeaveSecurityCommandFactory.CreatedEvent -= Poco::Delegate<EventDispatcher, LeaveSecurityCommand*&>(this, &EventDispatcher::HandleLeaveSecurityCommandFactoryCreatedEvent);
    theLeaveSecurityCommandFactory.DestroyedEvent -= Poco::Delegate<EventDispatcher, LeaveSecurityCommand*&>(this, &EventDispatcher::HandleLeaveSecurityCommandFactoryDestroyedEvent);
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

GameEventBuffer* EventDispatcher::CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType eSecurityGameEvent_SecurityGameEventBufferType, const std::string& strUUID)
{
    SecurityGameEvent_Dependencies aSecurityGameEvent_Dependencies(eSecurityGameEvent_SecurityGameEventBufferType, strUUID);
    GameEventBuffer* pGameEvent = m_aSecurityGameEventFactory.Create(aSecurityGameEvent_Dependencies);
    
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
void EventDispatcher::HandlePodCreatedEvent(const void* pSender, Pod*& pPod)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_CREATE, static_cast<AEntity*>(pPod));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandlePodUpdatedEvent(const void* pSender, Pod*& pPod)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_UPDATE, static_cast<AEntity*>(pPod));
    Enqueue(pGameEvent);}

void EventDispatcher::HandlePodDestroyedEvent(const void* pSender, Pod*& pPod)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_DESTROY, static_cast<AEntity*>(pPod));
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

// Event Consumer event response
void EventDispatcher::HandleJoinSecurityCommandFactoryCreatedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent += Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleJoinSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleJoinSecurityCommandFactoryDestroyedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent -= Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleJoinSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandFactoryCreatedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent += Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleLeaveSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandFactoryDestroyedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent -= Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleLeaveSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleJoinSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType_JOIN, strUUID);
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID)
{
    GameEventBuffer* pGameEvent = CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType_LEAVE, strUUID);
    Enqueue(pGameEvent);
}
