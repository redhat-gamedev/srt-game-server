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
void MessageConsumer::Enqueue(cms::BytesMessage* pBytesMessage)
{
    assert(pBytesMessage);
    
    Poco::Tuple<cms::BytesMessage*>*    pTuple = new Poco::Tuple<cms::BytesMessage*>(pBytesMessage);
    m_aTupleQueue.lock();
    m_aTupleQueue.push(pTuple);
    m_aTupleQueue.unlock();
}

// cms::MessageListener implementation
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
