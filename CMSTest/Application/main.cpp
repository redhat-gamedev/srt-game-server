/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "Server.h"
#include "activemq/library/ActiveMQCPP.h"
#include "Poco/BasicEvent.h"
#include "Poco/Delegate.h"
#include <iostream>

using namespace Poco;


class Source
{
public:
    BasicEvent<int> theEvent;
    
    void fireEvent(int n)
    {
        theEvent(this, n);
    }
};

class Target
{
public:
    void onEvent(const void* pSender, int& arg)
    {
        std::cout << "onEvent: " << arg << std::endl;
    }
};

int main(int argc, char* argv[])
{
    std::cout << "Starting..." << std::endl;
    
    Source source;
    Target target;
    
    source.theEvent += Delegate<Target, int>(&target, &Target::onEvent);
    
    source.fireEvent(42);
    
    source.theEvent -= Delegate<Target, int>(&target, &Target::onEvent);
    
    std::cout << "Initializing the ActiveMQCPP library" << std::endl;
    activemq::library::ActiveMQCPP::initializeLibrary();
    
    Server* pServer = new Server();

    //pServer->Run();
    
    // Wait to exit.
    std::cout << "Press 'q' to quit" << std::endl;
    while( std::cin.get() != 'q') {}

    delete pServer;
    pServer = NULL;
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
