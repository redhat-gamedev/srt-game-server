//
//  Server.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Server.h"
#include "SimpleAsyncConsumer.h"
#include "SimpleAsyncProducer.h"
#include "B2DWorld.h"
#include "Heartbeat.h"
#include "Addressbook.h"
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

StlQueue<std::string>      Server::s_ProducerQueue;
StlQueue<std::string>      Server::s_ConsumerQueue;

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;



// Constructor(s)
Server::Server() :
    m_pSimulationProducer(NULL),
    m_pHeartbeatProducer(NULL),
    m_pAddressbookProducer(NULL),
    m_pB2DWorldThread(NULL),
    m_pCommandConsumer(NULL),
    m_pB2DWorld(NULL),
    m_pTimer(NULL),
    m_ptAddressbook(NULL),
    m_pHeartbeat(NULL),
    m_pAddressbook(NULL)
{
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
    bool            useTopics = false;
    bool            clientAck = false;
    std::string     strName = "MySimpleProducerThread";
    std::string     strWorldSimulationURI = "WORLD.SIMULATION";
    std::string     strHeartbeatURI = "HEARTBEAT";
    std::string     strAddressURI = "ADDRESS";
    std::string     strInputURI = "CLIENT.INPUT";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    ///"failover:(tcp://127.0.0.1:61616"
    //        "?wireFormat=openwire"
    //        "&connection.useAsyncSend=true"
    //        "&transport.commandTracingEnabled=true"
    //        "&transport.tcpTracingEnabled=true"
    //        "&wireFormat.tightEncodingEnabled=true"
    ///")";
    
    std::cout << "Setup()..." << std::endl;
    
    activemq::library::ActiveMQCPP::initializeLibrary();
    
    m_pB2DWorld = new B2DWorld();
    m_pB2DWorld->CreateBodiesAndShapes();
    m_pB2DWorldThread = new decaf::lang::Thread(m_pB2DWorld, strName);
    
    m_pSimulationProducer = new SimpleProducer(strBrokerURI, strWorldSimulationURI, useTopics);
    m_pHeartbeatProducer = new SimpleProducer(strBrokerURI, strHeartbeatURI, useTopics);
    m_pAddressbookProducer = new SimpleProducer(strBrokerURI, strAddressURI, useTopics);
    m_pCommandConsumer = new SimpleAsyncConsumer(strBrokerURI, strInputURI, useTopics, clientAck);
    
    m_pHeartbeat = new Heartbeat();
    m_pTimer = new decaf::util::Timer();

    m_pAddressbook = new Addressbook();
    m_ptAddressbook = new decaf::util::Timer();
    
    B2DWorld::Publisher.Attach(this);
    Heartbeat::Publisher.Attach(this);
    Addressbook::Publisher.Attach(this);
}

void Server::Teardown()
{
    std::cout << "Teardown()..." << std::endl;
    
    Addressbook::Publisher.Detach(this);
    Heartbeat::Publisher.Detach(this);
    B2DWorld::Publisher.Detach(this);

    m_ptAddressbook->cancel();
    //delete m_pAddressbook;
    m_pAddressbook = NULL;
    
    delete m_ptAddressbook;
    m_ptAddressbook = NULL;
    
    m_pTimer->cancel();
    //delete m_pHeartbeat;
    m_pHeartbeat = NULL;

    delete m_pTimer;
    m_pTimer = NULL;    
    
    m_pCommandConsumer->close();
    delete m_pCommandConsumer;
    m_pCommandConsumer = NULL;

    m_pAddressbookProducer->close();
    delete m_pAddressbookProducer;
    m_pAddressbookProducer = NULL;
    
    m_pHeartbeatProducer->close();
    delete m_pHeartbeatProducer;
    m_pHeartbeatProducer = NULL;

    m_pSimulationProducer->close();
    delete m_pSimulationProducer;
    m_pSimulationProducer = NULL;

    delete m_pB2DWorldThread;
    m_pB2DWorldThread = NULL;
    
    delete m_pB2DWorld;
    m_pB2DWorld = NULL;
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}

// Method(s)
void Server::Run()
{
    // Receive incoming user commands
    std::cout << "Starting the m_pCommandConsumer" << std::endl;
    m_pCommandConsumer->runConsumer();
    
    // Run simulation step
    std::cout << "Starting the world simulation" << std::endl;
    m_pB2DWorldThread->start();
    
    // Check game rules
    
    // Update all object states
    
    //  if any client needs a world update
    // take world snapshot
    // Update clients if required
    
    std::cout << "Starting the heartbeat" << std::endl;
    m_pTimer->schedule(m_pHeartbeat, 0, 1000);
    
    std::cout << "Starting the addressbook" << std::endl;
    m_ptAddressbook->schedule(m_pAddressbook, 0, 2000);
}

// B2DWorld::ICallbacks implementation
void Server::OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle)
{
    assert(m_pSimulationProducer);
    
    static char m_szBuf[0xFF];
    static std::string strText = "";
    
    try
    {
        memset(m_szBuf, 0, sizeof(m_szBuf));
        //sprintf(m_szBuf, "%4.2f %4.2f %4.2f", position.x, position.y, angle);
        sprintf(m_szBuf, "%4.2f", b2vNewPosition.y);
        //printf("%s\n", m_szBuf);
        strText = m_szBuf;

        m_pSimulationProducer->Send(strText);
        strText.clear();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

// Heartbeat::ICallbacks implementation
void Server::OnBeat(int iBeat)
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

// Heartbeat::ICallbacks implementation
void Server::OnPerson(tutorial::Person* person)
{
    assert(person);
    
    static char m_szBuf[0xFF];
    static std::string strText = "";
    
    try
    {
        memset(m_szBuf, 0, sizeof(m_szBuf));
        sprintf(m_szBuf, "%i", person->id());
        //printf("%s\n", m_szBuf);
        //strText = m_szBuf;
        person->SerializeToString(&strText);
        const char* pucText = strText.c_str();
        unsigned long ulLength = strText.length();
        m_pAddressbookProducer->Send((const unsigned char*)pucText, (int)ulLength);
        //m_pAddressbookProducer->Send(pucText, ulLength);
        
        //person->SerializeToArray(pData, iSize);
        strText.clear();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}