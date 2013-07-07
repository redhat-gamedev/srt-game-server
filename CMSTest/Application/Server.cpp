//
//  Server.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Server.h"
#include "World.h"
#include "Heartbeat.h"
#include "Security.h"
#include "Messenger.h"
#include "Messenger_Consumer.h"
#include "Messenger_Producer.h"
#include "AEntity.h"
#include "../Game/Player.h"
#include "../Proto/box2d.pb.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include "../Shared/SimpleAsyncProducer.h"
#include "EventDispatcher.h"
#include "MessageDispatcher.h"
#include "PodFactory.h"
#include "BulletFactory.h"
#include "EntityGameEventFactory.h"
#include "Poco/Delegate.h"
#include "decaf/util/Timer.h"
#include "decaf/lang/Thread.h"
#include "decaf/lang/Runnable.h"
#include "decaf/util/concurrent/CountDownLatch.h"
#include "activemq/core/ActiveMQConnectionFactory.h"
#include "activemq/core/ActiveMQConnection.h"
#include "activemq/transport/DefaultTransportListener.h"
#include "activemq/library/ActiveMQCPP.h"
#include "decaf/lang/Integer.h"
#include "activemq/util/Config.h"
#include "decaf/util/Date.h"
#include "cms/Connection.h"
#include "cms/Session.h"
#include "cms/TextMessage.h"
#include "cms/BytesMessage.h"
#include "cms/MapMessage.h"
#include "cms/ExceptionListener.h"
#include "cms/MessageListener.h"
#include "decaf/net/URI.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;
using namespace box2d;


// Constructor(s)
Server::Server() :
    m_pHeartbeatProducer(NULL),
    m_pCommandConsumer(NULL),
    m_pWorld(NULL),
    m_pTimer(NULL),
    m_pHeartbeat(NULL),
    m_pInput(NULL),
    m_pSecurity(NULL),
    m_pMainThread(NULL)
{
    PodFactory&                 thePodFactory = PodFactory::Instance();
    BulletFactory&              theBulletFactory = BulletFactory::Instance();
    FactoryT<GameEvent, EntityGameEvent_Dependencies>&     theEntityGameEventFactory = FactoryT<GameEvent, EntityGameEvent_Dependencies>::Instance();
    EventDispatcher::_Dependencies theEventDispatcherDependencies(thePodFactory, theBulletFactory, theEntityGameEventFactory);
    
    EventDispatcher& m_anEventDispatcher = EventDispatcher::Instance(&theEventDispatcherDependencies);
    //EventDispatcher& anEventDispatcher = EventDispatcher::Instance();
    
    Setup();
}

// Destructor(s)
Server::~Server()
{
    Teardown();
}

// Helper(s)
void Server::Setup()
{
    std::cout << "Server::Setup()..." << std::endl;

    std::string     strMainThreadName = "ServerThread";
    
    Messenger::Setup();
    AEntity::ClassSetup();

    
    
    m_pWorld = new World();
    m_pInput = new Input();
    m_pSecurity = new Security();

    //m_pTimer = new decaf::util::Timer();
    //m_pHeartbeatProducer = new SimpleAsyncProducer(strBrokerURI, strHeartbeatURI, true);
    //m_pHeartbeat = new Heartbeat();
    //Heartbeat::EventPublisher.BeatEvent += Poco::Delegate<Server, const int&>(this, &Server::OnHeartBeatBeat);
    
    std::cout << "Starting the world producer" << std::endl;
    m_pMainThread = new decaf::lang::Thread(this, strMainThreadName);
    m_pMainThread->start();
}

void Server::Teardown()
{
    std::cout << "Teardown()..." << std::endl;

    delete m_pMainThread;
    m_pMainThread = NULL;
    
    //Heartbeat::EventPublisher.BeatEvent -= Poco::Delegate<Server, const int&>(this, &Server::OnHeartBeatBeat);

    //m_pTimer->cancel();
    //delete m_pHeartbeat;
    //m_pHeartbeat = NULL;

    //m_pHeartbeatProducer->close();
    //delete m_pHeartbeatProducer;
    //m_pHeartbeatProducer = NULL;
    
    //delete m_pTimer;
    //m_pTimer = NULL;
    
    delete m_pSecurity;
    m_pSecurity = NULL;
    
    delete m_pInput;
    m_pInput = NULL;

    //m_pCommandConsumer->close();
    //delete m_pCommandConsumer;
    //m_pCommandConsumer = NULL;

    delete m_pWorld;
    m_pWorld = NULL;
    
    AEntity::ClassTeardown();
    Messenger::Teardown();
}

// Method(s)
void Server::run()
{
    while (true)
    {
        // Receive incoming user commands
        Messenger::Consumer.ProcessReceivedMessages();
        
        // Run simulation step
        m_pWorld->Simulate();
        
        // Check game rules
        
        // Update all object states
        AEntity::Update();
        
        // if any client needs a world update take world snapshot
        // Update clients if required
        //Messenger::Producer.ProcessEnqueuedMessages();
        Messenger::GameEventProducer.ProcessEnqueuedMessages();
        
        decaf::lang::Thread::currentThread()->sleep(15);
    }
}

// Heartbeat Event response
void Server::OnHeartBeatBeat(const void* pSender, const int& iBeat)
{
    static char m_szBuf[0xFF];
    static std::string strText = "";
    
    try
    {
        memset(m_szBuf, 0, sizeof(m_szBuf));
        sprintf(m_szBuf, "%i", iBeat);
        //printf("%s\n", m_szBuf);
        strText = m_szBuf;
        
        m_pHeartbeatProducer->Send(strText);
        strText.clear();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}