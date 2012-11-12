//
//  SimpleAsyncProducer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-28.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "SimpleAsyncProducer.h"
#include "decaf/lang/Thread.h"
//#include "decaf/lang/Runnable.h"
#include "decaf/util/concurrent/CountDownLatch.h"
#include "decaf/lang/Long.h"
#include "decaf/util/Date.h"
#include "activemq/core/ActiveMQConnectionFactory.h"
#include "activemq/util/Config.h"
#include "activemq/library/ActiveMQCPP.h"
#include "cms/Connection.h"
#include "cms/Session.h"
#include "cms/TextMessage.h"
#include "cms/BytesMessage.h"
#include "cms/MapMessage.h"
#include "cms/ExceptionListener.h"
#include "cms/MessageListener.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>

using namespace activemq;
using namespace activemq::core;
using namespace decaf;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;


SimpleProducer::SimpleProducer(
                               const std::string& brokerURI,
                               unsigned int numMessages,
                               const std::string& destURI,
                               bool useTopic,
                               bool clientAck)
{
    connection = NULL;
    session = NULL;
    destination = NULL;
    producer = NULL;
    this->numMessages = numMessages;
    this->useTopic = useTopic;
    this->brokerURI = brokerURI;
    this->destURI = destURI;
    this->clientAck = clientAck;
    
    try
    {
        // Create a ConnectionFactory
        auto_ptr<ActiveMQConnectionFactory> connectionFactory(new ActiveMQConnectionFactory( brokerURI ) );
        
        // Create a Connection
        try
        {
            connection = connectionFactory->createConnection();
            connection->start();
        }
        catch( CMSException& e )
        {
            e.printStackTrace();
            throw e;
        }
        
        // Create a Session
        if( clientAck )
        {
            session = connection->createSession( Session::CLIENT_ACKNOWLEDGE );
        }
        else
        {
            session = connection->createSession( Session::AUTO_ACKNOWLEDGE );
        }
        
        // Create the destination (Topic or Queue)
        if( useTopic )
        {
            destination = session->createTopic( destURI );
        }
        else
        {
            destination = session->createQueue( destURI );
        }
        
        // Create a MessageProducer from the Session to the Topic or Queue
        producer = session->createProducer( destination );
        producer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
        
        // Create the Thread Id String
        //string threadIdStr = Long::toString( Thread::getId() );
        long long llThreadId = Thread::currentThread()->getId();
        string threadIdStr = Long::toString( llThreadId );
        
        B2DWorld::Publisher.Attach(this);
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }

}

SimpleProducer::~SimpleProducer()
{
    B2DWorld::Publisher.Detach(this);
    cleanup();
}

void SimpleProducer::close()
{
    this->cleanup();
}

void SimpleProducer::run()
{
//    try
//    {
//        std::string text = "";
//        TextMessage* message = NULL;
//        int ix = 0;
//        //for( unsigned int ix=0; ix<numMessages; ++ix )
//        while (true)
//        {
//            // Receive incoming user commands
//            
//            // Run simulation step
//            m_pB2DWorld->Update(text);
//            
//            // Check game rules
//            
//            // Update all object states
//            
//            //  if any client needs a world update
//                // take world snapshot
//                // Update clients if required
//            message = session->createTextMessage( text );
//            message->setIntProperty( "Integer", ix );
//            //printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
//            //printf("%s\n", message->getText().c_str());
//            producer->send( message );
//            //Thread::currentThread()->yield();
//            
//            delete message;
//            Thread::currentThread()->sleep(10);
//            ++ix;
//        }        
//    }
//    catch ( CMSException& e )
//    {
//        e.printStackTrace();
//    }
}

void SimpleProducer::cleanup()
{
    // Destroy resources.
    try
    {
        if( destination != NULL )
            delete destination;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    destination = NULL;
    
    try
    {
        if( producer != NULL )
            delete producer;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    producer = NULL;
    
    // Close open resources.
    try
    {
        if( session != NULL )
            session->close();
        if( connection != NULL )
            connection->close();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    
    try
    {
        if( session != NULL )
            delete session;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    session = NULL;
    
    try
    {
        if( connection != NULL )
            delete connection;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    connection = NULL;
}

// B2DWorld::ICallbacks implementation
void SimpleProducer::OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle)
{
    static int ix = 0;
    static char m_szBuf[0xFF];

    try
    {
        std::string strText = "";
        TextMessage* message = NULL;

        memset(m_szBuf, 0, sizeof(m_szBuf));
        //sprintf(m_szBuf, "%4.2f %4.2f %4.2f", position.x, position.y, angle);
        sprintf(m_szBuf, "%4.2f", b2vNewPosition.y);
        printf("%s\n", m_szBuf);
        strText = m_szBuf;
        
        message = session->createTextMessage( strText );
        ++ix;
        message->setIntProperty( "Integer", ix );
        //printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
        //printf("%s\n", message->getText().c_str());
        producer->send( message );
        //Thread::currentThread()->yield();
        
        delete message;
        strText.clear();
        //Thread::currentThread()->sleep(10);
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}
