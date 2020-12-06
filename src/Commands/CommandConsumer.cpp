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

#include "CommandConsumer.h"
#include "../Network/MessageConsumer.h"
#include <Poco/Delegate.h>
#include <cms/BytesMessage.h>
#include <cms/CMSException.h>
#include <vector>
#include <assert.h>

using namespace google::protobuf;


// Constructor
CommandConsumer::
_Dependencies::
_Dependencies(MessageConsumer* pMessageConsumer, FactoryT<redhatgamedev::srt::CommandBuffer, SecurityCommand_Dependencies>& anSecurityCommandFactory) :
    m_aSecurityCommandFactory(anSecurityCommandFactory),
    m_pMessageConsumer(pMessageConsumer)
{
    assert(m_pMessageConsumer);
}

// Destructor
CommandConsumer::
_Dependencies::
~_Dependencies()
{
    
}
              
// Constructor(s)
// Constructor
CommandConsumer::CommandConsumer(_Dependencies* pDependencies) :
    m_aSecurityCommandFactory(pDependencies->m_aSecurityCommandFactory)
{
    assert(pDependencies);
    
    m_pMessageConsumer = pDependencies->m_pMessageConsumer;
    
    assert(m_pMessageConsumer);
    
    m_pMessageConsumer->ReceivedCMSMessageEvent += Poco::Delegate<CommandConsumer, Poco::Tuple<cms::BytesMessage*>*& >(this, &CommandConsumer::HandleReceivedCMSMessageEvent);
    
}

// Destructor
CommandConsumer::~CommandConsumer()
{
    m_pMessageConsumer->ReceivedCMSMessageEvent -= Poco::Delegate<CommandConsumer, Poco::Tuple<cms::BytesMessage*>*& >(this, &CommandConsumer::HandleReceivedCMSMessageEvent);
}

// Helper(s)
void CommandConsumer::Enqueue(Poco::Tuple<cms::BytesMessage*>* pTuple)
{
    assert(pTuple);
    
    using namespace redhatgamedev::srt;
    
    cms::BytesMessage* pBytesMessage = pTuple->get<0>();
    std::pair<unsigned char*, unsigned long>* pMessagePair = MessageToPair(pBytesMessage);
    assert(pMessagePair);
    
    /// TODO: 08/03/13
    /// Obviously need more general command factory depending on the type of message payload received
    google::protobuf::Message* pMessage = m_aSecurityCommandFactory.Create(pMessagePair);
    
    auto* pNewTuple = new Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>(pBytesMessage, pMessage);
    
    //pTuple->set<1>(pMessage);
    m_aTupleQueue.lock();
    m_aTupleQueue.push(pNewTuple);
    m_aTupleQueue.unlock();
    
    //delete pMessagePair;
    delete pTuple;
}

std::pair<unsigned char*, unsigned long>* CommandConsumer::MessageToPair(cms::BytesMessage* pBytesMessage)
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

// Method(s)
void CommandConsumer::Consume()
{
    Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>* pTuple = NULL;
    m_aTupleQueue.lock();
    while (!m_aTupleQueue.empty())
    {
        pTuple = m_aTupleQueue.pop();
        CommandConsumedEvent(this, pTuple);
    }
    m_aTupleQueue.unlock();
}

// Event response
void CommandConsumer::HandleReceivedCMSMessageEvent(const void* pSender, Poco::Tuple<cms::BytesMessage*>*& pTuple)
{
    Enqueue(pTuple);
}
