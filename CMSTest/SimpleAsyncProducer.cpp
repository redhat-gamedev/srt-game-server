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
#include <assert.h>
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
                               const std::string& strBrokerURI,
                               const std::string& strDestinationURI,
                               bool bUseTopic,
                               bool bClientAck)
{
    m_pConnection = NULL;
    m_pSession = NULL;
    m_pDestination = NULL;
    m_pMessageProducer = NULL;
    this->m_bUseTopic = bUseTopic;
    this->m_strBrokerURI = strBrokerURI;
    this->m_strDestinationURI = strDestinationURI;
    this->m_bClientAck = bClientAck;
    
    try
    {
        Setup();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }

}

SimpleProducer::~SimpleProducer()
{
    Teardown();
}

// Helper(s)
void SimpleProducer::Setup()
{
    // Create a ConnectionFactory
    auto_ptr<ActiveMQConnectionFactory> m_pConnectionFactory(new ActiveMQConnectionFactory( m_strBrokerURI ) );
    
    // Create a Connection
    try
    {
        m_pConnection = m_pConnectionFactory->createConnection();
        m_pConnection->start();
    }
    catch( CMSException& e )
    {
        e.printStackTrace();
        throw e;
    }
    
    // Create a Session
    if( m_bClientAck )
    {
        m_pSession = m_pConnection->createSession( Session::CLIENT_ACKNOWLEDGE );
    }
    else
    {
        m_pSession = m_pConnection->createSession( Session::AUTO_ACKNOWLEDGE );
    }
    
    // Create the m_pDestination (Topic or Queue)
    if( m_bUseTopic )
    {
        m_pDestination = m_pSession->createTopic( m_strDestinationURI );
    }
    else
    {
        m_pDestination = m_pSession->createQueue( m_strDestinationURI );
    }
    
    // Create a MessageProducer from the Session to the Topic or Queue
    m_pMessageProducer = m_pSession->createProducer( m_pDestination );
    m_pMessageProducer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
    
    // Create the Thread Id String
    //string threadIdStr = Long::toString( Thread::getId() );
    //long long llThreadId = Thread::currentThread()->getId();
    //string threadIdStr = Long::toString( llThreadId );
}

void SimpleProducer::Teardown()
{
    // Destroy resources.
    try
    {
        if( m_pDestination != NULL )
            delete m_pDestination;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    m_pDestination = NULL;
    
    try
    {
        if( m_pMessageProducer != NULL )
            delete m_pMessageProducer;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    m_pMessageProducer = NULL;
    
    // Close open resources.
    try
    {
        if( m_pSession != NULL )
            m_pSession->close();
        if( m_pConnection != NULL )
            m_pConnection->close();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    
    try
    {
        if( m_pSession != NULL )
            delete m_pSession;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    m_pSession = NULL;
    
    try
    {
        if( m_pConnection != NULL )
            delete m_pConnection;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
    m_pConnection = NULL;    
}

void SimpleProducer::close()
{
    Teardown();
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
//            message = m_pSession->createTextMessage( text );
//            message->setIntProperty( "Integer", ix );
//            //printf( "Sent message #%d from thread %s\n", ix+1, threadIdStr.c_str() );
//            //printf("%s\n", message->getText().c_str());
//            m_pMessageProducer->send( message );
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

void SimpleProducer::Send(std::string& strToSend)
{
    static int ix = 0;
    TextMessage* pTextMessage = NULL;
    
    try
    {
        pTextMessage = m_pSession->createTextMessage( strToSend );
        ++ix;
        pTextMessage->setIntProperty( "Integer", ix );
        m_pMessageProducer->send( pTextMessage );
        
        delete pTextMessage;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

void SimpleProducer::Send(const unsigned char* pucArray, int iSize)
{
    assert(pucArray);
    assert(iSize > 0);
    
    static int ix = 0;
    BytesMessage* pBytesMessage = NULL;
    
    try
    {
        pBytesMessage = m_pSession->createBytesMessage(pucArray, iSize);
        ++ix;
        m_pMessageProducer->send(pBytesMessage);
        
        delete pBytesMessage;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

