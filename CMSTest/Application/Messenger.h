//
//  Messenger.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger__
#define __CMSTest__Messenger__

#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
//#include <decaf/lang/Runnable.h>
#include <string>

class EntityData;
namespace decaf
{
    namespace lang
    {
        class Thread;
    }
}


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
    
public:
    // World Simulation
    static _Producer    Producer;
    
    // Game Event
    static _Producer    GameEventProducer;
    static _Consumer    Consumer;
    
    // Class function(s)
    static void Setup();
    static void Teardown();
    //static void Send();
    
    // Entity Event response
    static void OnEntityCreated(const void* pSender, const EntityData& anEntityData);
    static void OnEntityDestroyed(const void* pSender, const EntityData& anEntityData);
    
    // decaf::lang::Runnable implementation
    //void run();
    
    static void SendUpdates();
};

#endif /* defined(__CMSTest__Messenger__) */
