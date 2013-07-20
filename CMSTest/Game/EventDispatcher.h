//
//  EventDispatcher.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__EventDispatcher__
#define __CMSTest__EventDispatcher__

#include "../Proto/GameEventBuffer.pb.h"
#include "../Proto/EntityGameEventBuffer.pb.h"
#include "EntityGameEventFactory.h"
#include "SecurityGameEventFactory.h"
//#include "../Shared/FactoryT.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
class AEntity;
class Player;
class Bullet;
class PodFactory;
class BulletFactory;
//class EntityGameEventFactory;
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
        FactoryT<usx::geofactions::GameEventBuffer, EntityGameEvent_Dependencies>&         m_anEntityGameEventFactory;
        FactoryT<usx::geofactions::GameEventBuffer, SecurityGameEvent_Dependencies>&       m_aSecurityGameEventFactory;
        
        // Constructor
        _Dependencies(PodFactory& aPodFactory,
                      BulletFactory& aBulletFactory,
                      FactoryT<usx::geofactions::GameEventBuffer, EntityGameEvent_Dependencies>& pEntityGameEventFactory,
                      FactoryT<usx::geofactions::GameEventBuffer, SecurityGameEvent_Dependencies>& aSecurityGameEventFactory);
        
        // Destructor
        ~_Dependencies();
    };

private:
protected:
    PodFactory&                     m_aPodFactory;
    BulletFactory&                  m_aBulletFactory;
    FactoryT<usx::geofactions::GameEventBuffer, EntityGameEvent_Dependencies>&              m_anEntityGameEventFactory;
    FactoryT<usx::geofactions::GameEventBuffer, SecurityGameEvent_Dependencies>&            m_aSecurityGameEventFactory;
    
    decaf::util::StlQueue<google::protobuf::Message*>       m_anEventQueue;

    // Helper(s)
    void                            Enqueue(google::protobuf::Message* pMessage);
    google::protobuf::Message*      Dequeue();
    usx::geofactions::GameEventBuffer*           CreateGameEvent(usx::geofactions::EntityGameEventBuffer_EntityGameEventBufferType eEntityGameEvent_EntityGameEventBufferType, AEntity* pEntity);

    usx::geofactions::GameEventBuffer*           CreateGameEvent(usx::geofactions::SecurityGameEventBuffer_SecurityGameEventBufferType eSecurityGameEvent_SecurityGameEventBufferType, const std::string& strUUID);
    
    // Constructor(s)
    EventDispatcher(_Dependencies* pDependencies);
    
    // Destructor
    ~EventDispatcher();

public:
    // Event(s)
    Poco::BasicEvent<google::protobuf::Message*&>   EventDispatchedEvent;
    
    // Singleton
    static EventDispatcher& Instance(_Dependencies* pDependencies = NULL)//unsigned int uiCapacity)
    {
        static EventDispatcher  anEventDispatcher(pDependencies);
        return anEventDispatcher;
    }

    // Method(s)
    // Dispatches all the events it has received to it's listeners
    void Dispatch();
    
    // Entity event response
    void HandlePodCreatedEvent(const void* pSender, Player*& pPlayer);
    void HandlePodUpdatedEvent(const void* pSender, Player*& pPlayer);
    void HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer);
    
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

#endif /* defined(__CMSTest__EventDispatcher__) */
