//
//  MessageConsumer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-10.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "MessageConsumer.h"
#include "../Shared/SimpleAsyncConsumer.h"
#include <cms/BytesMessage.h>
#include <cms/CMSException.h>
#include <google/protobuf/message.h>
#include <string.h>
#include <string>
#include <assert.h>


// Constructor
MessageConsumer::
_Dependencies::
_Dependencies(SimpleAsyncConsumer* pSimpleAsyncConsumer) :
    m_pSimpleAsyncConsumer(pSimpleAsyncConsumer)
{
    assert(m_pSimpleAsyncConsumer);
}

// Destructor
MessageConsumer::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
MessageConsumer::MessageConsumer(_Dependencies* pDependencies)
{
    assert(pDependencies);
    
    m_pSimpleAsyncConsumer = pDependencies->m_pSimpleAsyncConsumer;
    
    assert(m_pSimpleAsyncConsumer);
    m_pSimpleAsyncConsumer->runConsumer();
    m_pSimpleAsyncConsumer->SetMessageListener(this);
}

// Destructor
MessageConsumer::~MessageConsumer()
{
    m_pSimpleAsyncConsumer->close();
    delete m_pSimpleAsyncConsumer;
    m_pSimpleAsyncConsumer = NULL;
}

// Helper(s)
void MessageConsumer::Enqueue(std::pair<unsigned char*, unsigned long>* pMessagePair)
{
    m_aMessageQueue.lock();
    m_aMessageQueue.push(pMessagePair);
    m_aMessageQueue.unlock();
}

void MessageConsumer::Enqueue(const cms::Message* pMessage)
{
    assert(pMessage);
    
    std::pair<unsigned char*, unsigned long>* pMessagePair = MessageToPair(pMessage);
    if (!pMessagePair)
    {
        return;
    }
    
    Enqueue(pMessagePair);
}

std::pair<unsigned char*, unsigned long>* MessageConsumer::MessageToPair(const cms::Message* pMessage)
{
    assert(pMessage);
    
    using namespace std;
    using namespace cms;
    
    pair<unsigned char*, unsigned long>*    pMessagePair = NULL;
    
    if (NULL == pMessage)
    {
        return NULL;
    }

    const BytesMessage* pBytesMessage = dynamic_cast<const BytesMessage*>(pMessage);
    int iBodyLength = pBytesMessage->getBodyLength();
    unsigned char* pucBodyBytesCopy = new unsigned char[iBodyLength];
    memcpy(pucBodyBytesCopy, pBytesMessage->getBodyBytes(), iBodyLength * sizeof(unsigned char));
    pMessagePair = new pair<unsigned char*, unsigned long>(pucBodyBytesCopy, iBodyLength);
    
    return pMessagePair;
    
}

// MessageListener implementation
void MessageConsumer::onMessage(const cms::Message* pMessage)
{
    assert(pMessage);

    Enqueue(pMessage);
}

// Method(s)
// Dispatches all the messages it has received from the network
// via the configured simple async consumer
void MessageConsumer::Dispatch()
{
    // TODO: Used ScopedLock (?)
    try
    {
        m_aMessageQueue.lock();
        while (!m_aMessageQueue.empty())
        {
                std::pair<unsigned char*, unsigned long>* pMessagePair = m_aMessageQueue.pop();
                if (pMessagePair->second > 0)
                {
                    ReceivedCMSMessageEvent(this, pMessagePair);
                }
        }
        m_aMessageQueue.unlock();
    }
    catch ( cms::CMSException& e )
    {
        e.printStackTrace();
    }
}
