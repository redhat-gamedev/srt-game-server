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
#include "cms/Destination.h"
#include "cms/AsyncCallback.h"
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


// Constructor(s)
SimpleAsyncProducer::SimpleAsyncProducer(
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
    m_bOwnDestination = true;
    
    try
    {
        Setup();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

SimpleAsyncProducer::SimpleAsyncProducer(const std::string& strBrokerURI,
               const cms::Destination* pDestination,
               bool bUseTopic,
               bool bClientAck)
{
    m_pConnection = NULL;
    m_pSession = NULL;
    m_pDestination = (Destination*)pDestination;
    m_pMessageProducer = NULL;
    this->m_bUseTopic = bUseTopic;
    this->m_strBrokerURI = strBrokerURI;
    this->m_bClientAck = bClientAck;
    m_bOwnDestination = false;
    
    try
    {
        Setup();
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

SimpleAsyncProducer::~SimpleAsyncProducer()
{
    Teardown();
}

// Helper(s)
void SimpleAsyncProducer::Setup()
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
    if (NULL == m_pDestination)
    {
        if (m_bUseTopic)
        {
            m_pDestination = m_pSession->createTopic( m_strDestinationURI );
        }
        else
        {
            m_pDestination = m_pSession->createQueue( m_strDestinationURI );
        }
    }
    // Create a MessageProducer from the Session to the Topic or Queue
    m_pMessageProducer = m_pSession->createProducer( m_pDestination );
    m_pMessageProducer->setDeliveryMode( DeliveryMode::NON_PERSISTENT );
    
    // Create the Thread Id String
    //string threadIdStr = Long::toString( Thread::getId() );
    //long long llThreadId = Thread::currentThread()->getId();
    //string threadIdStr = Long::toString( llThreadId );
}

void SimpleAsyncProducer::Teardown()
{
    // Destroy resources.
    try
    {
        if( m_pDestination != NULL )
            if (m_bOwnDestination)
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

void SimpleAsyncProducer::close()
{
    Teardown();
}

void SimpleAsyncProducer::run()
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

void SimpleAsyncProducer::Send(std::string& strToSend, cms::AsyncCallback* pAsyncCallback)
{
    static int ix = 0;
    TextMessage* pTextMessage = NULL;
    
    try
    {
        pTextMessage = m_pSession->createTextMessage( strToSend );
        ++ix;
        pTextMessage->setIntProperty( "Integer", ix );
        if (pAsyncCallback)
        {
            m_pMessageProducer->send(pTextMessage, pAsyncCallback);
        }
        else
        {
            m_pMessageProducer->send(pTextMessage);
        }
        
        delete pTextMessage;
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

void SimpleAsyncProducer::Send(const unsigned char* pucArray, int iSize)
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
