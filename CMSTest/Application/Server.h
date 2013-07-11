//
//  Server.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Server__
#define __CMSTest__Server__

#include "EventDispatcher.h"
#include "EventConsumer.h"
#include "MessageDispatcher.h"
#include "MessageConsumer.h"
#include "../Game/B2DWorld.h"
#include "../Game/Input.h"
#include "../Proto/box2d.pb.h"
#include <decaf/lang/Runnable.h>
#include <string>

namespace decaf
{
    namespace lang
    {
        class Thread;
    }
    namespace util
    {
        class Timer;
    }
}
class Security;
class World;
class Player;

using namespace decaf::lang;


class Server :
    public decaf::lang::Runnable
{
// Class
private:
    
protected:

public:
    
// Instance
private:
    
protected:
    Input*                  m_pInput;
    Security*               m_pSecurity;
    World*                  m_pWorld;
    
    decaf::lang::Thread*    m_pMainThread;
    
    EventDispatcher&        m_theEventDispatcher;
    EventConsumer&          m_theEventConsumer;
    MessageDispatcher&      m_theMessageDispatcher;
    MessageConsumer&        m_theMessageConsumer;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
public:
    // Constructor(s)
    Server(EventDispatcher& theEventDispatcher, EventConsumer& theEventConsumer, MessageDispatcher& theMessageDispatcher, MessageConsumer& theMessageConsumer);
    
    // Destructor(s)
    ~Server();
    
    // Method(s)
    // decaf::lang::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Server__) */
