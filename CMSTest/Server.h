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
//#include "decaf/lang/Thread.h"
//#include "decaf/util/Timer.h"
#include "B2DWorld.h"
#include "Heartbeat.h"
#include "Input.h"
#include "Security.h"
#include "Addressbook.h"
#include "addressbook.pb.h"
#include "box2d.pb.h"
#include "../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
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
//class B2DWorld;
class Player;

using namespace decaf::lang;
using namespace decaf::util;


class Server :
    public B2DWorld::ICallbacks,
    public Heartbeat::ICallbacks,
    public Security::ICallbacks,
    public Addressbook::ICallbacks
{
// Class
private:
    
protected:

public:
    static StlQueue<std::string>      s_ProducerQueue;
    static StlQueue<std::string>      s_ConsumerQueue;
    
// Instance
private:
    
protected:
    SimpleProducer*         m_pSimulationProducer;
    SimpleProducer*         m_pHeartbeatProducer;
    SimpleProducer*         m_pAddressbookProducer;
    Thread*                 m_pB2DWorldThread;
    SimpleAsyncConsumer*    m_pCommandConsumer;
    B2DWorld*               m_pB2DWorld;
    Timer*                  m_pTimer;
    Timer*                  m_ptAddressbook;
    Heartbeat*              m_pHeartbeat;
    Addressbook*            m_pAddressbook;
    Input*                  m_pInput;
    Security*               m_pSecurity;
    Player*                 m_pPlayer;
    
    
    // Helper(s)
    void Setup();
    void Teardown();
    void b2Vec2ToPbVec2(b2Vec2* pb2Vec2);
    void b2WorldToPbWorld(b2World* pb2World, ::box2d::PbWorld*& pPbWorldDefault, std::string& strPBBuffer);
    
public:
    // Constructor(s)
    Server();
    
    // Destructor(s)
    ~Server();
    
    // Method(s)
    void Run();
    
    
    // B2DWorld::ICallbacks implementation
    //void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle);
    void OnB2DWorldUpdate(b2World* pWorld);
    void OnB2DWorldBodyUpdate(b2Body* pBody);
    
    // Heartbeat::ICallbacks implementation
    void OnBeat(int iBeat);
    
    // Addressbook::ICallbacks implementation
    void OnPerson(tutorial::Person* person);

    // Security::ICallbacks implementation
    void OnSecurityJoin(std::string& strUUID);
};

#endif /* defined(__CMSTest__Server__) */
