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

#include "MessageConsumer.h"
#include "SimpleAsyncConsumer.h"
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
