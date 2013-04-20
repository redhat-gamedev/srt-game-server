//
//  Input.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Input.h"
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include <cms/CMSException.h>
//#include <cms/Message.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <iostream>

using namespace DualStick;
using namespace box2d;
using namespace cms;

Input::_Publisher                 Input::Publisher;

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
void Input::_Publisher::OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot)
{
    ICallbacks* pObjToCallback = NULL;
    
    //m_listSubscribersSwap = m_listSubscribers;
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnDualStick(strUUID, pbv2Move, pbv2Shoot);
    }
}

// Constructor(s)
Input::Input() :
    m_pSimpleAsyncConsumer(NULL)
{
    bool            useTopics = false;
    bool            clientAck = false;
    std::string     strInputURI = "CLIENT.INPUT";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";

    std::cout << "Input::Input()..." << std::endl;
    
    m_pSimpleAsyncConsumer = new SimpleAsyncConsumer(strBrokerURI, strInputURI, useTopics, clientAck);
    m_pSimpleAsyncConsumer->runConsumer();
    m_pSimpleAsyncConsumer->SetMessageListener(this);
}

// Destructor
Input::~Input()
{
    m_pSimpleAsyncConsumer->close();
    delete m_pSimpleAsyncConsumer;
    m_pSimpleAsyncConsumer = NULL;
}

// MessageListener implementation
void Input::onMessage(const Message* pMessage)
{
    assert(pMessage);
    
    static int count = 0;
    //bool            clientAck = false;
    PbDualStick aDualStick;
    std::string     strNMSXGroupIDPropertyName = "NMSXGroupID";
    std::string     strNMSXGroupID = "";
    std::string     strUUID = "";
    
    try
    {
        count++;
        const BytesMessage* pBytesMessage = dynamic_cast<const BytesMessage*>(pMessage);
        assert(pBytesMessage);

        unsigned char* pucBodyBytes = pBytesMessage->getBodyBytes();
        int iBodyBytes = pBytesMessage->getBodyLength();
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        aDualStick.ParseFromArray(pucBodyBytes, iBodyBytes);
        
        if (pBytesMessage->propertyExists(strNMSXGroupIDPropertyName))
        {
            strNMSXGroupID = pBytesMessage->getStringProperty(strNMSXGroupIDPropertyName);
        }
        //if(clientAck)
        //{
        //    pMessage->acknowledge();
        //}
        
        const PbVec2& pbv2Move = aDualStick.pbv2move();
        const PbVec2& pbv2Shoot = aDualStick.pbv2shoot();
        const std::string& strUUID = aDualStick.uuid();
        
        Publisher.OnDualStick(strUUID, pbv2Move, pbv2Shoot);
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}