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
    class _Consumer;

    static const std::string        BrokerURI;
    
    //static decaf::lang::Thread*     s_pThread;
    
    // Constructor(s)
    Messenger();
    
    // Destructor(s)
    ~Messenger();

public:
    // Game Event
    static _Consumer    Consumer;
    
    // Class function(s)
    static void Setup();
    static void Teardown();
    
    // decaf::lang::Runnable implementation
    //void run();
    
    static void SendUpdates();
};

#endif /* defined(__CMSTest__Messenger__) */
