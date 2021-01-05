//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "Server.h"
#include "../Game/World.h"
#include "../Game/AEntity.h"
#include "decaf/lang/Thread.h"
#include "decaf/lang/Runnable.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "../Logging/loguru.hpp"


// Constructor(s)
Server::Server(EventDispatcher& theEventDispatcher,
               MessageDispatcher& theMessageDispatcher,
               MessageConsumer& theMessageConsumer,
               CommandConsumer& theCommandConsumer,
               CommandQueue& theCommandQueue) :
    m_pWorld(NULL),
    //m_pInput(NULL),
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
    LOG_SCOPE_F(INFO, "Setting up Server");

    std::string     strMainThreadName = "ServerThread";
    
    AEntity::ClassSetup();

    m_pWorld = new World();
    //m_pInput = new Input();

    LOG_SCOPE_F(INFO, "Starting the world producer");
    m_pMainThread = new decaf::lang::Thread(this, strMainThreadName);
    m_pMainThread->start();
}

void Server::Teardown()
{
    LOG_SCOPE_F(INFO, "Tearing down the server...");

    delete m_pMainThread;
    m_pMainThread = NULL;
    
//    delete m_pInput;
//    m_pInput = NULL;

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
