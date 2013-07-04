//
//  Messenger.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger__
#define __CMSTest__Messenger__

#include "../Game/AEntity.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
//#include <decaf/lang/Runnable.h>
#include <string>

namespace decaf
{
    namespace lang
    {
        class Thread;
    }
}
class Bullet;
class Player;


class Messenger// :
//    decaf::lang::Runnable
{
private:
    
protected:
    class _Producer;
    class _Consumer;

    static const std::string        BrokerURI;
    static xdispatch::queue*        s_pMessengerSerialDispatchQueue;
    
    //static decaf::lang::Thread*     s_pThread;
    
    // Constructor(s)
    Messenger();
    
    // Destructor(s)
    ~Messenger();
    
    // Helper(s)
    static void EnqueueEntityCreatedEvent(AEntity* pEntity);
    static void EnqueueEntityUpdatedEvent(AEntity* pEntity);
    static void EnqueueEntityDestroyedEvent(AEntity* pEntity);
    
    
public:
    // World Simulation
    //static _Producer    Producer;
    
    // Game Event
    static _Producer    GameEventProducer;
    static _Consumer    Consumer;
    
    // Class function(s)
    static void Setup();
    static void Teardown();
    //static void Send();
    
    // Entity Event response
    static void OnEntityCreated(const void* pSender, const AEntity::EType& anEntityType);
    static void OnEntityUpdated(const void* pSender, const AEntity::EType& anEntityType);
    static void OnEntityDestroyed(const void* pSender, const AEntity::EType& anEntityType);

    static void HandlePodCreatedEvent(const void* pSender, Player*& pPlayer);
    static void HandlePodUpdatedEvent(const void* pSender, Player*& pPlayer);
    static void HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer);
    
    static void HandleBulletCreatedEvent(const void* pSender, Bullet*& pBullet);
    static void HandleBulletUpdatedEvent(const void* pSender, Bullet*& pBullet);
    static void HandleBulletDestroyedEvent(const void* pSender, Bullet*& pBullet);
    
    // decaf::lang::Runnable implementation
    //void run();
    
    static void SendUpdates();
};

#endif /* defined(__CMSTest__Messenger__) */
