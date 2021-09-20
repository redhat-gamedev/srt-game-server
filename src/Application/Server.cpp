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

#include "Configuration.h"
#include "Server.h"
#include "../Game/World.h"
#include "../Game/AEntity.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <assert.h>
#include "../Logging/loguru.hpp"


// Constructor(s)
Server::Server(EventDispatcher& theEventDispatcher,
               MessageDispatcher& theMessageDispatcher,
               MessageConsumer& theMessageConsumer,
               CommandConsumer& theCommandConsumer,
               CommandQueue& theCommandQueue) :
    m_pWorld(NULL),
    m_pMainThread(NULL),
    m_bStop(false),
    m_bIsStopped(false),
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
}

void Server::Teardown()
{
    LOG_SCOPE_F(INFO, "Tearing down the server...");

    m_pMainThread->join();
    delete m_pMainThread;
    m_pMainThread = NULL;
    
    delete m_pWorld;
    m_pWorld = NULL;
    
    AEntity::ClassTeardown();
}

// Method(s)
void Server::run()
{
    while (!m_bStop)
    {
		LOG_SCOPE_FUNCTION(2);
        // Receive incoming user commands
        LOG_F(2, "Handling incoming commands");
        LOG_F(4, "Message Consumer Dispatch");
        m_theMessageConsumer.Dispatch();
        LOG_F(4, "Command Consumer Consume");
        m_theCommandConsumer.Consume();
        LOG_F(4, "Command Queue Execute");
        m_theCommandQueue.Execute();
        
        // Run simulation step
        LOG_F(2, "Simulating");
        m_pWorld->Simulate();
        
        // Check game rules
        
        // Update all object states
        LOG_F(2, "Update the objects");
        AEntity::Update();

        // if any client needs a world update take world snapshot
        // Update clients if required
        LOG_F(2, "Telling the clients what's going on");
        LOG_F(4, "Event Dispatcher Dispatch");
        m_theEventDispatcher.Dispatch();
        LOG_F(4, "Message Dispatcher Dispatch");
        m_theMessageDispatcher.Dispatch();
        
        LOG_F(4, "Game Sleep");
        std::this_thread::sleep_for(std::chrono::milliseconds(Configuration::Instance().SleepCycle));
    }
    m_bIsStopped = true;
}

void Server::Stop()
{
    m_bStop = true;
}

void Server::Launch()
{
    LOG_SCOPE_F(INFO, "Starting the main Server thread");
    m_pMainThread = new std::thread([this]() {run();});
}
