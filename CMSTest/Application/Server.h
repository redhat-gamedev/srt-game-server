//
//  Server.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Server__
#define __CMSTest__Server__

#include "decaf/util/StlQueue.h"
#include "Heartbeat.h"
#include "Security.h"
#include "../Game/B2DWorld.h"
#include "../Game/Input.h"
#include "../Proto/box2d.pb.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
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
class SimpleProducer;
class SimpleAsyncConsumer;
//class Security;
//class Heartbeat;
class World;
class Player;

using namespace decaf::lang;


class Server :
    public Heartbeat::ICallbacks,
    public Security::ICallbacks
{
// Class
private:
    
protected:

public:
    
// Instance
private:
    
protected:
    SimpleProducer*         m_pHeartbeatProducer;
    SimpleAsyncConsumer*    m_pCommandConsumer;
    decaf::util::Timer*     m_pTimer;
    Heartbeat*              m_pHeartbeat;
    Input*                  m_pInput;
    Security*               m_pSecurity;
    World*                  m_pWorld;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
public:
    // Constructor(s)
    Server();
    
    // Destructor(s)
    ~Server();
    
    // Method(s)
    void Run();
    
    // Heartbeat::ICallbacks implementation
    void OnBeat(int iBeat);    
};

#endif /* defined(__CMSTest__Server__) */
