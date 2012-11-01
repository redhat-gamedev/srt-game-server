
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



#if 1
////////////////////////////////////////////////////////////////////////////////
int main(int argc AMQCPP_UNUSED, char* argv[] AMQCPP_UNUSED)
{
    bool            useTopics = false;
    bool            clientAck = false;
    unsigned int    numMessages = 20000;
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
    
    std::cout << "Starting..." << std::endl;
    activemq::library::ActiveMQCPP::initializeLibrary();

    // Create the producer and run it.
    //    SimpleProducer producer( brokerURI, numMessages, destURI, useTopics );
    //    producer.run();
    //    producer.close();
    SimpleProducer producer(strBrokerURI, numMessages, strWorldSimulationURI, useTopics);
    Thread pSimpleProducerThread(&producer, (char*)"MySimpleProducerThread");
    
    std::cout << "Starting the producer" << std::endl;
    pSimpleProducerThread.start();
    
    SimpleAsyncConsumer consumer(strBrokerURI, strInputURI, useTopics, clientAck);
    // Start it up and it will listen forever.
    std::cout << "Starting the consumer" << std::endl;
    consumer.runConsumer();
    // Wait to exit.
    std::cout << "Press 'q' to quit" << std::endl;
    while( std::cin.get() != 'q') {}
    
    consumer.close();
    
//    std::cout << "Waiting for the producer thread to terminate..." << std::endl;
//    while (Thread::TERMINATED != pSimpleProducerThread.getState())
//    {
//    }
//    std::cout << "...Finished." << std::endl;

    producer.close();
    
    activemq::library::ActiveMQCPP::shutdownLibrary();
}
#endif



#if 0
////////////////////////////////////////////////////////////////////////////////
// Original Consumer main
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

#if 0
////////////////////////////////////////////////////////////////////////////////
// Original Producer main
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

////////////////////////////////////////////////////////////////////////////////
// Original Box2D Hello World main
////////////////////////////////////////////////////////////////////////////////
#if 0
/*
 * Copyright (c) 2006-2007 Erin Catto http://www.gphysics.com
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

//#include "Box2D.h"
#include "../../../iPhone/Libraries/Box2D/Include/Box2D.h"

//#include <cstdio>

// This is a simple example of building and running a simulation
// using Box2D. Here we create a large ground box and a small dynamic
// box.
int main(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
    
	// Define the size of the world. Simulation will still work
	// if bodies reach the end of the world, but it will be slower.
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-100.0f, -100.0f);
	worldAABB.upperBound.Set(100.0f, 100.0f);
    
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);
    
	// Do we want to let bodies sleep?
	bool doSleep = true;
    
	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(worldAABB, gravity, doSleep);
    
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
	// Define the ground box shape.
	b2PolygonDef groundShapeDef;
    
	// The extents are the half-widths of the box.
	groundShapeDef.SetAsBox(50.0f, 10.0f);
    
	// Add the ground shape to the ground body.
	groundBody->CreateShape(&groundShapeDef);
    
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.position.Set(0.0f, 4.0f);
	b2Body* body = world.CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	b2PolygonDef shapeDef;
	shapeDef.SetAsBox(1.0f, 1.0f);
    
	// Set the box density to be non-zero, so it will be dynamic.
	shapeDef.density = 1.0f;
    
	// Override the default friction.
	shapeDef.friction = 0.3f;
    
	// Add the shape to the body.
	body->CreateShape(&shapeDef);
    
	// Now tell the dynamic body to compute it's mass properties base
	// on its shape.
	body->SetMassFromShapes();
    
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 iterations = 10;
    
	// This is our little game loop.
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation. It is
		// generally best to keep the time step and iterations fixed.
		world.Step(timeStep, iterations);
        
		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
        
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}
    
	// When the world destructor is called, all bodies and joints are freed. This can
	// create orphaned pointers, so be careful about your world management.
    
	return 0;
}
#endif

