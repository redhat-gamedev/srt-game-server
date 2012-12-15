//
//  Security.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Security.h"
#include "DualStick.pb.h"
#include "box2d.pb.h"
#include "SimpleAsyncConsumer.h"
#include <cms/CMSException.h>
//#include <cms/Message.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/Destination.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>

using namespace DualStick;
using namespace box2d;
using namespace cms;

Security::_Publisher                 Security::Publisher;

// Constructor(s)
/*
 B2DWorld.h::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 B2DWorld.h::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void Security::_Publisher::OnPlayerJoin(std::string strUUID)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnPlayerJoin(strUUID);
    }
}

// Constructor(s)
Security::Security() :
    m_pSimpleAsyncConsumer(NULL),
    m_pSimpleAsyncProducer(NULL)
{
    bool            useTopics = false;
    bool            clientAck = false;
    std::string     strSecurityURI = "AAS.IN";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";

    std::cout << "Security::Security()..." << std::endl;
    
    m_pSimpleAsyncConsumer = new SimpleAsyncConsumer(strBrokerURI, strSecurityURI, useTopics, clientAck);
    m_pSimpleAsyncConsumer->runConsumer();
    m_pSimpleAsyncConsumer->SetMessageListener(this);
}

// Destructor
Security::~Security()
{
    m_pSimpleAsyncConsumer->close();
    delete m_pSimpleAsyncConsumer;
    m_pSimpleAsyncConsumer = NULL;
}

// MessageListener implementation
void Security::onMessage(const Message* pMessage)
{
    assert(pMessage);
    
    static int      count = 0;
    bool            clientAck = false;
    PbDualStick     aDualStick;
    
    try
    {
        count++;
        const BytesMessage* pBytesMessage = dynamic_cast<const BytesMessage*>(pMessage);
        assert(pBytesMessage);

        unsigned char* pucBodyBytes = pBytesMessage->getBodyBytes();
        int iBodyBytes = pBytesMessage->getBodyLength();
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        if(clientAck)
        {
            pMessage->acknowledge();
        }
        
        const cms::Destination* pDestination = pBytesMessage->getCMSReplyTo();
        assert(pDestination);

        std::string strUUID = "UUID";
        m_mapUUIDToReplyDestinations.insert(std::pair<std::string, const cms::Destination*>(strUUID, pDestination));
        
        Publisher.OnPlayerJoin(strUUID);
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}
