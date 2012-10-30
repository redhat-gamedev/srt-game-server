//
//  SimpleAsyncConsumer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-28.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "SimpleAsyncConsumer.h"
#include <decaf/lang/Thread.h>
//#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
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


SimpleAsyncConsumer::SimpleAsyncConsumer(
                    const std::string& brokerURI,
                    const std::string& destURI,
                    bool useTopic,
                    bool clientAck)
{
    connection = NULL;
    session = NULL;
    destination = NULL;
    consumer = NULL;
    this->useTopic = useTopic;
    this->brokerURI = brokerURI;
    this->destURI = destURI;
    this->clientAck = clientAck;
}

SimpleAsyncConsumer::~SimpleAsyncConsumer()
{
    this->cleanup();
}

void SimpleAsyncConsumer::close()
{
    this->cleanup();
}

void SimpleAsyncConsumer::runConsumer()
{
    try {
        
        const std::string& strBrokerURI = brokerURI;
        // Create a ConnectionFactory
        //ActiveMQConnectionFactory* connectionFactory = new ActiveMQConnectionFactory( brokerURI );
        ActiveMQConnectionFactory* connectionFactory = new ActiveMQConnectionFactory();// strBrokerURI );
        //connectionFactory->setBrokerURI(strBrokerURI);
        decaf::net::URI* uriBroker = new decaf::net::URI(strBrokerURI);
        connectionFactory->setBrokerURI(*uriBroker);
        
        
        // Create a Connection
        connection = connectionFactory->createConnection();
        delete connectionFactory;
        
        ActiveMQConnection* amqConnection = dynamic_cast<ActiveMQConnection*>( connection );
        if( amqConnection != NULL ) {
            amqConnection->addTransportListener( this );
        }
        
        connection->start();
        
        connection->setExceptionListener(this);
        
        // Create a Session
        if( clientAck ) {
            session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
        } else {
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
        }
        
        // Create the destination (Topic or Queue)
        if( useTopic ) {
            destination = session->createTopic( destURI );
        } else {
            destination = session->createQueue( destURI );
        }
        
        // Create a MessageConsumer from the Session to the Topic or Queue
        consumer = session->createConsumer( destination );
        consumer->setMessageListener( this );
        
    } catch (CMSException& e) {
        e.printStackTrace();
    }
}

// Called from the consumer since this class is a registered MessageListener.
void SimpleAsyncConsumer::onMessage( const Message* message )
{
    
    static int count = 0;
    
    try
    {
        count++;
        const TextMessage* textMessage =
        dynamic_cast< const TextMessage* >( message );
        string text = "";
        
        if( textMessage != NULL ) {
            text = textMessage->getText();
        } else {
            text = "NOT A TEXTMESSAGE!";
        }
        
        if( clientAck ) {
            message->acknowledge();
        }
        
        printf( "Message #%d Received: %s\n", count, text.c_str() );
    } catch (CMSException& e) {
        e.printStackTrace();
    }
}

// If something bad happens you see it here as this class is also been
// registered as an ExceptionListener with the connection.
void SimpleAsyncConsumer::onException( const CMSException& ex AMQCPP_UNUSED )
{
    printf("CMS Exception occurred.  Shutting down client.\n");
    //exit(1);
}

void SimpleAsyncConsumer::transportInterrupted()
{
    std::cout << "The Connection's Transport has been Interrupted." << std::endl;
}

void SimpleAsyncConsumer::transportResumed()
{
    std::cout << "The Connection's Transport has been Restored." << std::endl;
}

void SimpleAsyncConsumer::cleanup()
{
    //*************************************************
    // Always close destination, consumers and producers before
    // you destroy their sessions and connection.
    //*************************************************
    
    // Destroy resources.
    try{
        if( destination != NULL ) delete destination;
    }catch (CMSException& e) {}
    destination = NULL;
    
    try{
        if( consumer != NULL ) delete consumer;
    }catch (CMSException& e) {}
    consumer = NULL;
    
    // Close open resources.
    try{
        if( session != NULL ) session->close();
        if( connection != NULL ) connection->close();
    }catch (CMSException& e) {}
    
    // Now Destroy them
    try{
        if( session != NULL ) delete session;
    }catch (CMSException& e) {}
    session = NULL;
    
    try{
        if( connection != NULL ) delete connection;
    }catch (CMSException& e) {}
    connection = NULL;
}