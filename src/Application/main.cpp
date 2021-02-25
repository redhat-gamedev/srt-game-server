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
#include "../Network/MessageDispatcher.h"
#include "../Network/MessageConsumer.h"
#include "../Commands/SecurityCommand.h"
#include "../Commands/JoinSecurityCommand.h"
#include "../Commands/LeaveSecurityCommand.h"
#include "../Network/sender.h"
#include "../Network/receiver.h"
#include "../Events/EventDispatcher.h"
#include "../Commands/CommandConsumer.h"
#include "../Commands/CommandQueue.h"
#include "../Game/PodFactory.h"
#include "../Game/BulletFactory.h"
#include "../Events/EntityGameEventFactory.h"
#include "../Events/SecurityGameEventFactory.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include "../Proto/RawInputCommandBuffer.pb.h"
#include "../Commands/SecurityCommandBufferFactory.h"
#include "../Shared/FactoryT.h"
#include <iostream>
#include "../Logging/loguru.cpp"


void usage(char **argv) {
    fprintf(stderr, "usage: %s [options]\n", argv[0]);
    fprintf(stderr, "  --help: print usage\n");
    fprintf(stderr, "  --broker-uri: broker uri with options e.g. tcp://127.0.0.1:5672\n");
    fprintf(stderr, "  --sleep-cycle: the time (in milliseconds) of the server sleep (default 15) \n");
    fprintf(stderr, " ");
    fprintf(stderr, "\n\n");
}

int main(int argc, char* argv[])
{
    // First see if they are looking to display usage via --help as first argument
    if (0 == strcmp(argv[0], "--help"))
    {
        usage(argv);
        exit(0);
    }

	loguru::init(argc, argv);
	LOG_F(INFO, "Space Ring Things - Game Server");

	Configuration &config = Configuration::Instance();
	config.Init(argc, argv);

    // Run the proton container
    proton::container container;
    auto container_thread = std::thread([&]() { container.run(); });

    // A single sender and receiver to be shared by all the threads
    // TODO: Proton TEST ME
    sender send(container, config.BrokerUri, config.GameEventOut);
    receiver recv(container, config.BrokerUri, config.CommandIn);

    PodFactory&                     thePodFactory = PodFactory::Instance();
    BulletFactory&                  theBulletFactory = BulletFactory::Instance();
    auto&                           theEntityGameEventFactory = FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>::Instance();
    auto&                           theSecurityGameEventFactory = FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>::Instance();
    EventDispatcher::_Dependencies  theEventDispatcherDependencies(thePodFactory, theBulletFactory, theEntityGameEventFactory, theSecurityGameEventFactory);
    EventDispatcher&                theEventDispatcher = EventDispatcher::Instance(&theEventDispatcherDependencies);

    LOG_F(INFO, "main creating MessageDispatcher with strBrokerURI: %s", Configuration::Instance().BrokerUri.c_str());
    MessageDispatcher::_Dependencies    theMessageDispatcherDependencies(&send);
    MessageDispatcher&                  theMessageDispatcher = MessageDispatcher::Instance(&theMessageDispatcherDependencies);

    LOG_F(INFO, "main creating MessageConsumer with strBrokerURI: %s", Configuration::Instance().BrokerUri.c_str());
    MessageConsumer::_Dependencies      theMessageConsumerDependencies(&recv);
    MessageConsumer&                    theMessageConsumer = MessageConsumer::Instance(&theMessageConsumerDependencies);

    auto&                               theSecurityCommandBufferFactory = FactoryT<redhatgamedev::srt::CommandBuffer, SecurityCommand_Dependencies>::Instance();
    CommandConsumer::_Dependencies      theCommandConsumerDependencies(&theMessageConsumer, theSecurityCommandBufferFactory);
    CommandConsumer&                    theCommandConsumer = CommandConsumer::Instance(&theCommandConsumerDependencies);
    
    auto&                           theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, JoinSecurityCommand::_SecurityDependencies>::Instance();
    auto&                           theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, LeaveSecurityCommand::_SecurityDependencies>::Instance();
    auto&                           theDualStickRawInputCommandFactory = FactoryT<DualStickRawInputCommand, DualStickRawInputCommand::_RawInputDependencies>::Instance();
    CommandQueue::_Dependencies     theCommandQueueDependencies(theJoinSecurityCommandFactory, theLeaveSecurityCommandFactory, theDualStickRawInputCommandFactory, theCommandConsumer);
    CommandQueue&                   theCommandQueue = CommandQueue::Instance(&theCommandQueueDependencies);
    
    Server* pServer = new Server(theEventDispatcher, theMessageDispatcher, theMessageConsumer, theCommandConsumer, theCommandQueue);

    // Wait to exit.
    LOG_F(INFO, "press 'q' to quit");
    while( std::cin.get() != 'q') {}

    pServer->stop();

    send.close();
    recv.close();

    delete pServer;
    pServer = NULL;

    return 0;
}
