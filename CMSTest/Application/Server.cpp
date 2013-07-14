//
//  Server.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Server.h"
#include "World.h"
//#include "Security.h"
#include "AEntity.h"
#include "decaf/lang/Thread.h"
#include "decaf/lang/Runnable.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>


// Constructor(s)
Server::Server(EventDispatcher& theEventDispatcher,
               MessageDispatcher& theMessageDispatcher,
               MessageConsumer& theMessageConsumer,
               CommandConsumer& theCommandConsumer,
               CommandQueue& theCommandQueue) :
    m_pWorld(NULL),
    m_pInput(NULL),
//    m_pSecurity(NULL),
    m_pMainThread(NULL),
    m_theEventDispatcher(theEventDispatcher),
    m_theMessageDispatcher(theMessageDispatcher),
    m_theMessageConsumer(theMessageConsumer),
    m_theCommandConsumer(theCommandConsumer),
    m_theCommandQueue(theCommandQueue)
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
    std::cout << "Server::Setup()..." << std::endl;

    std::string     strMainThreadName = "ServerThread";
    
    AEntity::ClassSetup();

    m_pWorld = new World();
    m_pInput = new Input();
//    m_pSecurity = new Security();

    std::cout << "Starting the world producer" << std::endl;
    m_pMainThread = new decaf::lang::Thread(this, strMainThreadName);
    m_pMainThread->start();
}

void Server::Teardown()
{
    std::cout << "Teardown()..." << std::endl;

    delete m_pMainThread;
    m_pMainThread = NULL;
    
//    delete m_pSecurity;
//    m_pSecurity = NULL;
    
    delete m_pInput;
    m_pInput = NULL;

    delete m_pWorld;
    m_pWorld = NULL;
    
    AEntity::ClassTeardown();
}

// Method(s)
void Server::run()
{
    while (true)
    {
        // Receive incoming user commands
        m_theMessageConsumer.Dispatch();
        m_theCommandConsumer.Consume();
        m_theCommandQueue.Execute();
        
        // Run simulation step
        m_pWorld->Simulate();
        
        // Check game rules
        
        // Update all object states
        AEntity::Update();

        // if any client needs a world update take world snapshot
        // Update clients if required
        m_theEventDispatcher.Dispatch();
        m_theMessageDispatcher.Dispatch();
        
        decaf::lang::Thread::currentThread()->sleep(15);
    }
}
