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
#include "MessageDispatcher.h"
#include "MessageConsumer.h"
#include "SecurityCommand.h"
#include "../Shared/SimpleAsyncProducer.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include "../Game/EventDispatcher.h"
#include "../Game/CommandConsumer.h"
#include "../Game/CommandQueue.h"
#include "../Game/PodFactory.h"
#include "../Game/BulletFactory.h"
#include "../Game/EntityGameEventFactory.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include "../Game/SecurityCommandBufferFactory.h"
#include "../Shared/FactoryT.h"
#include "activemq/library/ActiveMQCPP.h"
#include <iostream>

//class Base
//{
//public:
//    virtual void Func()
//    {
//        std::cout << "Base::Func()" << std::endl;
//    }
//};
//
//
//class Derived :
//    public Base
//{
//public:
//    virtual void Func()
//    {
//        std::cout << "Derived::Func()" << std::endl;
//    }
//};


int main(int argc, char* argv[])
{
    //std::string     strSecurityInURI = "AAS.IN";
    //std::string     strSecurityOutURI = "AAS.OUT";
    //std::string     strGameEventInDestinationURI = "GAME.EVENT.IN";
    
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    std::string     strCommandInDestinationURI = "COMMAND.IN";
    std::string     strGameEventOutDestinationURI = "GAME.EVENT.OUT";
    
    std::cout << "Starting..." << std::endl;
    std::cout << "Initializing the ActiveMQCPP library" << std::endl;
    activemq::library::ActiveMQCPP::initializeLibrary();
    
//    Base aBase;
//    Derived aDerived;
//    
//    aBase.Func();
//    aDerived.Func();
//    Base& aBaseReference = aDerived;
//    aBaseReference.Func();
    
    PodFactory&                                                 thePodFactory = PodFactory::Instance();
    BulletFactory&                                              theBulletFactory = BulletFactory::Instance();
    FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>&          theEntityGameEventFactory = FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>::Instance();
    EventDispatcher::_Dependencies                              theEventDispatcherDependencies(thePodFactory, theBulletFactory, theEntityGameEventFactory);
    EventDispatcher&                                            theEventDispatcher = EventDispatcher::Instance(&theEventDispatcherDependencies);
    
    SimpleAsyncProducer*                                        pSimpleAsyncProducer = new SimpleAsyncProducer(strBrokerURI, strGameEventOutDestinationURI, true);
    MessageDispatcher::_Dependencies                            theMessageDispatcherDependencies(pSimpleAsyncProducer);
    MessageDispatcher&                                          theMessageDispatcher = MessageDispatcher::Instance(&theMessageDispatcherDependencies);
    
    SimpleAsyncConsumer*                                        pSimpleAsyncConsumer = new SimpleAsyncConsumer(strBrokerURI, strCommandInDestinationURI);
    MessageConsumer::_Dependencies                              theMessageConsumerDependencies(pSimpleAsyncConsumer);
    MessageConsumer&                                            theMessageConsumer = MessageConsumer::Instance(&theMessageConsumerDependencies);

    FactoryT<CommandBuffers::CommandBuffer, SecurityCommand_Dependencies>&     theSecurityCommandBufferFactory = FactoryT<CommandBuffers::CommandBuffer, SecurityCommand_Dependencies>::Instance();
    CommandConsumer::_Dependencies                                theCommandConsumerDependencies(&theMessageConsumer, theSecurityCommandBufferFactory);
    CommandConsumer&                                              theCommandConsumer = CommandConsumer::Instance(&theCommandConsumerDependencies);
    
    FactoryT<::SecurityCommand, ::SecurityCommand::_SecurityDependencies>&      theSecurityCommandFactory = FactoryT<::SecurityCommand, ::SecurityCommand::_SecurityDependencies>::Instance();
    CommandQueue::_Dependencies                                 theCommandQueueDependencies(theSecurityCommandFactory, theCommandConsumer);
    CommandQueue&                                               theCommandQueue = CommandQueue::Instance(&theCommandQueueDependencies);
    
    Server* pServer = new Server(theEventDispatcher,
                                 theMessageDispatcher,
                                 theMessageConsumer,
                                 theCommandConsumer,
                                 theCommandQueue);

    //pServer->run();
    
    // Wait to exit.
    std::cout << "Press 'q' to quit" << std::endl;
    while( std::cin.get() != 'q') {}

    delete pServer;
    pServer = NULL;
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
