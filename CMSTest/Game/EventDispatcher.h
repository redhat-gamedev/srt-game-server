//
//  EventDispatcher.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__EventDispatcher__
#define __CMSTest__EventDispatcher__

#include "../proto/GameEvent.pb.h"
#include "../proto/EntityGameEvent.pb.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>

//using namespace decaf;
//using namespace decaf::util;

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
class EntityGameEventFactory;


class EventDispatcher
{
private:
protected:
    EntityGameEventFactory&                                 m_anEntityGameEventFactory;
    decaf::util::StlQueue<google::protobuf::Message*>       m_anEventQueue;

    // Helper(s)
    void                            Enqueue(google::protobuf::Message* pMessage);
    google::protobuf::Message*      Dequeue();
    gameevent::GameEvent*           CreateGameEvent(gameevent::EntityGameEvent_EntityGameEventType eEntityGameEvent_EntityGameEventType, AEntity* pEntity);
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        PodFactory&                     m_aPodFactory;
        BulletFactory&                  m_aBulletFactory;
        EntityGameEventFactory&         m_anEntityGameEventFactory;
        
        // Constructor
        _Dependencies(PodFactory& aPodFactory, BulletFactory& aBulletFactory, EntityGameEventFactory& pEntityGameEventFactory);
        
        // Destructor
        ~_Dependencies();
    };
    
    // Event(s)
    Poco::BasicEvent<google::protobuf::Message*&>   EventDispatchedEvent;
    
    // Constructor(s)
    EventDispatcher(_Dependencies& theDependencies);
    
    // Destructor
    ~EventDispatcher();
    
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
};

#endif /* defined(__CMSTest__EventDispatcher__) */
