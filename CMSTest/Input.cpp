//
//  Input.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Input.h"
#include "DualStick.pb.h"
#include "box2d.pb.h"
#include "SimpleAsyncConsumer.h"
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


// Constructor(s)
Input::Input() :
    m_pSimpleAsyncConsumer(NULL)
{
    bool            useTopics = false;
    bool            clientAck = false;
    std::string     strInputURI = "CLIENT.INPUT";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";

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
    bool            clientAck = false;
    PbDualStick aDualStick;
    
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
        
        if(clientAck)
        {
            pMessage->acknowledge();
        }
        
        printf("Bytes Message #%d Received\n", count);
        //printf("Bytes Message #%d Received\n", count);
        const PbVec2& pbv2Move = aDualStick.pbv2move();
        const PbVec2& pbv2Shoot = aDualStick.pbv2shoot();
        
        printf("h[%4.4f] v[%4.4f]\n", pbv2Move.x(), pbv2Move.y());
        printf("fh[%4.4f] fv[%4.4f]\n", pbv2Shoot.x(), pbv2Shoot.y());
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}