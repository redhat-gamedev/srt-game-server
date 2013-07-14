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
//    m_aTupleQueue.lock();
//    m_aTupleQueue.push(pMessagePair);
//    m_aTupleQueue.unlock();
}

void MessageConsumer::Enqueue(cms::BytesMessage* pBytesMessage)
{
    assert(pBytesMessage);
    
//    std::pair<unsigned char*, unsigned long>* pMessagePair = MessageToPair(pMessage);
//    if (!pMessagePair)
//    {
//        return;
//    }
//    
//    Enqueue(pMessagePair);
    
    Poco::Tuple<cms::BytesMessage*>*    pTuple = new Poco::Tuple<cms::BytesMessage*>(pBytesMessage);
    
    m_aTupleQueue.lock();
    m_aTupleQueue.push(pTuple);
    m_aTupleQueue.unlock();
}

std::pair<unsigned char*, unsigned long>* MessageConsumer::MessageToPair(cms::BytesMessage* pBytesMessage)
{
    assert(pBytesMessage);
    
    using namespace std;
    using namespace cms;
    
    pair<unsigned char*, unsigned long>*    pMessagePair = NULL;
    
    pBytesMessage->reset();
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
    
    cms::Message* pMessageClone = pMessage->clone();
    cms::BytesMessage* pBytesMessage = dynamic_cast<cms::BytesMessage*>(pMessageClone);

    Enqueue(pBytesMessage);
}

// Method(s)
// Dispatches all the messages it has received from the network
// via the configured simple async consumer
void MessageConsumer::Dispatch()
{
    // TODO: Used ScopedLock (?)
    try
    {
        m_aTupleQueue.lock();
        while (!m_aTupleQueue.empty())
        {
            Poco::Tuple<cms::BytesMessage*>*  pTuple = m_aTupleQueue.pop();
            ReceivedCMSMessageEvent(this, pTuple);
        }
        m_aTupleQueue.unlock();
    }
    catch ( cms::CMSException& e )
    {
        e.printStackTrace();
    }
}
