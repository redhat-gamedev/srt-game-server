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

#include "Input.h"
#if 0
#include "../Application/Configuration.h"
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "../Network/SimpleAsyncConsumer.h"
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

Input::_EventPublisher            Input::EventPublisher;


// Constructor(s)
Input::Input() :
    m_pSimpleAsyncConsumer(NULL)
{
    bool            useTopics = false;
    bool            clientAck = false;
    std::string     strInputURI = "CLIENT.INPUT";

    std::cout << "Input::Input()..." << std::endl;
    
    m_pSimpleAsyncConsumer = new SimpleAsyncConsumer(Configuration::Instance().BrokerURI, strInputURI, useTopics, clientAck);
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
        
        FireDualStickEvent(aDualStick);
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
}

// Event Firing Method(s)
void Input::FireDualStickEvent(DualStick::PbDualStick aPbDualStick)
{
    EventPublisher.DualStickEvent(this, aPbDualStick);
}
#endif
