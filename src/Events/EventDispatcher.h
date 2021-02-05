#ifndef __SRT__EventDispatcher__
#define __SRT__EventDispatcher__

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

#include "../Proto/GameEventBuffer.pb.h"
#include "../Proto/EntityGameEventBuffer.pb.h"
#include "EntityGameEventFactory.h"
#include "SecurityGameEventFactory.h"
#include <Poco/BasicEvent.h>
#include <queue>
#include <mutex>

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
class AEntity;
class Pod;
class Bullet;
class PodFactory;
class BulletFactory;
class EntityGameEvent_Dependencies;
class SecurityGameEvent_Dependencies;
class JoinSecurityCommand;
class LeaveSecurityCommand;


class EventDispatcher
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        PodFactory&                     m_aPodFactory;
        BulletFactory&                  m_aBulletFactory;
        FactoryT<redhatgamedev::srt::GameEventBuffer, EntityGameEvent_Dependencies>&         m_anEntityGameEventFactory;
        FactoryT<redhatgamedev::srt::GameEventBuffer, SecurityGameEvent_Dependencies>&       m_aSecurityGameEventFactory;
        
        // Constructor
        _Dependencies(PodFactory& aPodFactory,
                      BulletFactory& aBulletFactory,
                      FactoryT<redhatgamedev::srt::GameEventBuffer, EntityGameEvent_Dependencies>& pEntityGameEventFactory,
                      FactoryT<redhatgamedev::srt::GameEventBuffer, SecurityGameEvent_Dependencies>& aSecurityGameEventFactory);
        
        // Destructor
        ~_Dependencies();
    };

private:
protected:
    PodFactory&                     m_aPodFactory;
    BulletFactory&                  m_aBulletFactory;
    FactoryT<redhatgamedev::srt::GameEventBuffer, EntityGameEvent_Dependencies>&              m_anEntityGameEventFactory;
    FactoryT<redhatgamedev::srt::GameEventBuffer, SecurityGameEvent_Dependencies>&            m_aSecurityGameEventFactory;

    std::queue<google::protobuf::Message*>       m_anEventQueue;
    std::mutex                                   m_anEventQueueMutex;

    // Helper(s)
    void                            Enqueue(google::protobuf::Message* pMessage);
    google::protobuf::Message*      Dequeue();
    redhatgamedev::srt::GameEventBuffer*           CreateGameEvent(redhatgamedev::srt::EntityGameEventBuffer_EntityGameEventBufferType eEntityGameEvent_EntityGameEventBufferType, AEntity* pEntity);

    redhatgamedev::srt::GameEventBuffer*           CreateGameEvent(redhatgamedev::srt::SecurityGameEventBuffer_SecurityGameEventBufferType eSecurityGameEvent_SecurityGameEventBufferType, const std::string& strUUID);
    
    // Constructor(s)
    EventDispatcher(_Dependencies* pDependencies);
    
    // Destructor
    ~EventDispatcher();

public:
    // Event(s)
    Poco::BasicEvent<google::protobuf::Message*&>   EventDispatchedEvent;
    
    // Singleton
    static EventDispatcher& Instance(_Dependencies* pDependencies = NULL)
    {
        static EventDispatcher  anEventDispatcher(pDependencies);
        return anEventDispatcher;
    }

    // Method(s)
    // Dispatches all the events it has received to it's listeners
    void Dispatch();
    
    // Entity event response
    void HandlePodCreatedEvent(const void* pSender, Pod*& pPod);
    void HandlePodUpdatedEvent(const void* pSender, Pod*& pPod);
    void HandlePodDestroyedEvent(const void* pSender, Pod*& pPod);
    
    void HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet);
    void HandleBulletUpdatedEvent(const void* pSender, Bullet*& pBullet);
    void HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet);
    
    // Event Consumer event response
    void HandleJoinSecurityCommandFactoryCreatedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand);
    void HandleJoinSecurityCommandFactoryDestroyedEvent(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand);
    void HandleLeaveSecurityCommandFactoryCreatedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand);
    void HandleLeaveSecurityCommandFactoryDestroyedEvent(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand);
    
    void HandleJoinSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID);
    void HandleLeaveSecurityCommandExecutedEvent(const void* pSender, const std::string& strUUID);
};


#endif /* defined(__SRT__EventDispatcher__) */
