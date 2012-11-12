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
    producer(NULL),
    pSimpleProducerThread(NULL),
    consumer(NULL),
    m_pB2DWorld(NULL)
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
    unsigned int    numMessages = 20000;
    std::string     strName = "MySimpleProducerThread";
    std::string     strWorldSimulationURI = "WORLD.SIMULATION";
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
    //pSimpleProducerThread = new decaf::lang::Thread(producer, strName);
    pSimpleProducerThread = new decaf::lang::Thread(m_pB2DWorld, strName);
    
    producer = new SimpleProducer(strBrokerURI, numMessages, strWorldSimulationURI, useTopics);
    consumer = new SimpleAsyncConsumer(strBrokerURI, strInputURI, useTopics, clientAck);
}

void Server::Teardown()
{
    std::cout << "Teardown()..." << std::endl;
    
    consumer->close();
    delete consumer;
    consumer = NULL;
    
    producer->close();
    delete producer;
    producer = NULL;

    delete pSimpleProducerThread;
    pSimpleProducerThread = NULL;
    
    delete m_pB2DWorld;
    m_pB2DWorld = NULL;
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}

// Method(s)
void Server::Run()
{
    // Receive incoming user commands
    std::cout << "Starting the consumer" << std::endl;
    consumer->runConsumer();
    
    // Run simulation step
    //m_pB2DWorld->Update(text);
    
    // Check game rules
    
    // Update all object states
    
    //  if any client needs a world update
    // take world snapshot
    // Update clients if required
    
    std::cout << "Starting the producer" << std::endl;
    pSimpleProducerThread->start();
}
