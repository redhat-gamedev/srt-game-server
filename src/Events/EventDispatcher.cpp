//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

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
#include "../Logging/loguru.hpp"
#include <Poco/Delegate.h>
#include <assert.h>

using namespace redhatgamedev::srt;
using namespace google::protobuf;


// Constructor
EventDispatcher::
_Dependencies::
_Dependencies(PodFactory& aPodFactory,
              BulletFactory& aBulletFactory,
              FactoryT<redhatgamedev::srt::GameEventBuffer, EntityGameEvent_Dependencies>& anEntityGameEventFactory,
              FactoryT<redhatgamedev::srt::GameEventBuffer, SecurityGameEvent_Dependencies>& aSecurityGameEventFactory) :
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
    LOG_SCOPE_FUNCTION(8);
    m_anEventQueueMutex.lock();
    m_anEventQueue.push(pMessage);
    m_anEventQueueMutex.unlock();
}

Message* EventDispatcher::Dequeue()
{
    LOG_SCOPE_FUNCTION(8);
    Message* pMessage = NULL;

    m_anEventQueueMutex.lock();
    pMessage = m_anEventQueue.front();
    m_anEventQueue.pop();
    m_anEventQueueMutex.unlock();
    
    return pMessage;
}

GameEventBuffer* EventDispatcher::CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType eEntityGameEvent_EntityGameEventBufferType, AEntity* pEntity)
{
    LOG_SCOPE_FUNCTION(8);
    LOG_F(8, "Entity Game Event");
    EntityGameEvent_Dependencies anEntityGameEvent_Dependencies(eEntityGameEvent_EntityGameEventBufferType, pEntity);
    GameEventBuffer* pGameEvent = m_anEntityGameEventFactory.Create(anEntityGameEvent_Dependencies);
    
    return pGameEvent;
}

GameEventBuffer* EventDispatcher::CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType eSecurityGameEvent_SecurityGameEventBufferType, const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(8);
    LOG_F(8, "Security Game Event");
    SecurityGameEvent_Dependencies aSecurityGameEvent_Dependencies(eSecurityGameEvent_SecurityGameEventBufferType, strUUID);
    GameEventBuffer* pGameEvent = m_aSecurityGameEventFactory.Create(aSecurityGameEvent_Dependencies);
    
    return pGameEvent;
}
// Method(s)
// Dispatches all the events it has received to it's listeners
void EventDispatcher::Dispatch()
{
    LOG_SCOPE_FUNCTION(8);
    Message* pMessage = NULL;
    m_anEventQueueMutex.lock();
    while (!m_anEventQueue.empty())
    {
        pMessage = m_anEventQueue.front();
        m_anEventQueue.pop();
        EventDispatchedEvent(this, pMessage);
    }
    m_anEventQueueMutex.unlock();
}

// Entity event response
void EventDispatcher::HandlePodCreatedEvent(const void* pSender, Pod*& pPod)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_CREATE, static_cast<AEntity*>(pPod));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandlePodUpdatedEvent(const void* pSender, Pod*& pPod)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_UPDATE, static_cast<AEntity*>(pPod));
    Enqueue(pGameEvent);}

void EventDispatcher::HandlePodDestroyedEvent(const void* pSender, Pod*& pPod)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_DESTROY, static_cast<AEntity*>(pPod));
    Enqueue(pGameEvent);}

void EventDispatcher::HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_CREATE, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleBulletUpdatedEvent(const void* pSender, Bullet*& pBullet)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_UPDATE, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(EntityGameEventBuffer_EntityGameEventBufferType_DESTROY, static_cast<AEntity*>(pBullet));
    Enqueue(pGameEvent);
}

// Event Consumer event response
void EventDispatcher::HandleJoinSecurityCommandFactoryCreatedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    LOG_SCOPE_FUNCTION(8);
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent += Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleJoinSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleJoinSecurityCommandFactoryDestroyedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    LOG_SCOPE_FUNCTION(8);
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent -= Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleJoinSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandFactoryCreatedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    LOG_SCOPE_FUNCTION(8);
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent += Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleLeaveSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandFactoryDestroyedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    LOG_SCOPE_FUNCTION(8);
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent -= Poco::Delegate<EventDispatcher, const std::string&>(this, &EventDispatcher::HandleLeaveSecurityCommandExecutedEvent);
}

void EventDispatcher::HandleJoinSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType_JOIN, strUUID);
    Enqueue(pGameEvent);
}

void EventDispatcher::HandleLeaveSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(8);
    GameEventBuffer* pGameEvent = CreateGameEvent(SecurityGameEventBuffer_SecurityGameEventBufferType_LEAVE, strUUID);
    Enqueue(pGameEvent);
}
