
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

#include "SimpleAsyncConsumer.h"
#include "SimpleAsyncProducer.h"

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <decaf/net/URI.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;


#if 0
////////////////////////////////////////////////////////////////////////////////
int main(int argc AMQCPP_UNUSED, char* argv[] AMQCPP_UNUSED) {
    
    activemq::library::ActiveMQCPP::initializeLibrary();
    
    std::cout << "=====================================================\n";
    std::cout << "Starting the example:" << std::endl;
    std::cout << "-----------------------------------------------------\n";
    
    // Set the URI to point to the IPAddress of your broker.
    // add any optional params to the url to enable things like
    // tightMarshalling or tcp logging etc.  See the CMS web site for
    // a full list of configuration options.
    //
    //  http://activemq.apache.org/cms/
    //
    // Wire Format Options:
    // =====================
    // Use either stomp or openwire, the default ports are different for each
    //
    // Examples:
    //    tcp://127.0.0.1:61616                      default to openwire
    //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
    //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
    //
    std::string brokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    ///"failover:(tcp://127.0.0.1:61616"
    //        "?wireFormat=openwire"
    //        "&connection.useAsyncSend=true"
    //        "&transport.commandTracingEnabled=true"
    //        "&transport.tcpTracingEnabled=true"
    //        "&wireFormat.tightEncodingEnabled=true"
    ///")";
    
    //============================================================
    // This is the Destination Name and URI options.  Use this to
    // customize where the consumer listens, to have the consumer
    // use a topic or queue set the 'useTopics' flag.
    //============================================================
    std::string destURI = "TEST.FOO"; //?consumer.prefetchSize=1";
    
    //============================================================
    // set to true to use topics instead of queues
    // Note in the code above that this causes createTopic or
    // createQueue to be used in the consumer.
    //============================================================
    bool useTopics = false;
    
    //============================================================
    // set to true if you want the consumer to use client ack mode
    // instead of the default auto ack mode.
    //============================================================
    bool clientAck = false;
    
    // Create the consumer
    SimpleAsyncConsumer consumer( brokerURI, destURI, useTopics, clientAck );
    
    // Start it up and it will listen forever.
    consumer.runConsumer();
    
    // Wait to exit.
    std::cout << "Press 'q' to quit" << std::endl;
    while( std::cin.get() != 'q') {}
    
    // All CMS resources should be closed before the library is shutdown.
    consumer.close();
    
    std::cout << "-----------------------------------------------------\n";
    std::cout << "Finished with the example." << std::endl;
    std::cout << "=====================================================\n";
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
#endif

#if 1
////////////////////////////////////////////////////////////////////////////////
int main(int argc AMQCPP_UNUSED, char* argv[] AMQCPP_UNUSED)
{    
    activemq::library::ActiveMQCPP::initializeLibrary();
    
    std::cout << "=====================================================\n";
    std::cout << "Starting the example:" << std::endl;
    std::cout << "-----------------------------------------------------\n";
    
    // Set the URI to point to the IPAddress of your broker.
    // add any optional params to the url to enable things like
    // tightMarshalling or tcp logging etc.  See the CMS web site for
    // a full list of configuration options.
    //
    //  http://activemq.apache.org/cms/
    //
    // Wire Format Options:
    // =====================
    // Use either stomp or openwire, the default ports are different for each
    //
    // Examples:
    //    tcp://127.0.0.1:61616                      default to openwire
    //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
    //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
    //
    std::string brokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    ///"failover:(tcp://127.0.0.1:61616"
    //        "?wireFormat=openwire"
    //        "&connection.useAsyncSend=true"
    //        "&transport.commandTracingEnabled=true"
    //        "&transport.tcpTracingEnabled=true"
    //        "&wireFormat.tightEncodingEnabled=true"
    ///")";
    
    //============================================================
    // Total number of messages for this producer to send.
    //============================================================
    unsigned int numMessages = 2000;
    
    //============================================================
    // This is the Destination Name and URI options.  Use this to
    // customize where the Producer produces, to have the producer
    // use a topic or queue set the 'useTopics' flag.
    //============================================================
    std::string destURI = "TEST.FOO";
    
    //============================================================
    // set to true to use topics instead of queues
    // Note in the code above that this causes createTopic or
    // createQueue to be used in the producer.
    //============================================================
    bool useTopics = false;
    
    
    
    
    // Create the producer and run it.
//    SimpleProducer producer( brokerURI, numMessages, destURI, useTopics );
//    producer.run();
//    producer.close();
    
    SimpleProducer producer(brokerURI, numMessages, destURI, useTopics);
    Thread pSimpleProducerThread(&producer, (char*)"MySimpleProducerThread");
    pSimpleProducerThread.start();
    //producer.run();
    std::cout << "Waiting for the producer thread to terminate..." << std::endl;
    while (Thread::TERMINATED != pSimpleProducerThread.getState())
    {
    }

    std::cout << "-----------------------------------------------------\n";
    std::cout << "Finished with the example." << std::endl;
    std::cout << "Closing out the producer." << std::endl;
    std::cout << "=====================================================\n";
    producer.close();
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
    
    //delete pSimpleProducerThread;
}
#endif


