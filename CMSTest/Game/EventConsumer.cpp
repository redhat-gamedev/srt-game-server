//
//  EventConsumer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-10.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "EventConsumer.h"
#include "MessageConsumer.h"
//#include "../Proto/GameEvent.pb.h"
//ls #include "../Proto/EntityGameEvent.pb.h"
#include "Poco/Delegate.h"
#include <vector>
#include <assert.h>

using namespace google::protobuf;


// Constructor
EventConsumer::
_Dependencies::
_Dependencies(MessageConsumer* pMessageConsumer, FactoryT<gameevent::GameEvent, EntityGameEvent_Dependencies>& anEntityGameEventFactory) :
    m_anEntityGameEventFactory(anEntityGameEventFactory),
    m_pMessageConsumer(pMessageConsumer)
{
    assert(m_pMessageConsumer);
}

// Destructor
EventConsumer::
_Dependencies::
~_Dependencies()
{
    
}
              
// Constructor(s)
// Constructor
EventConsumer::EventConsumer(_Dependencies* pDependencies) :
    m_anEntityGameEventFactory(pDependencies->m_anEntityGameEventFactory)
{
    assert(pDependencies);
    
    m_pMessageConsumer = pDependencies->m_pMessageConsumer;
    
    assert(m_pMessageConsumer);
    
    m_pMessageConsumer->ReceivedCMSMessageEvent += Poco::Delegate<EventConsumer, std::pair<unsigned char*, unsigned long>*& >(this, &EventConsumer::HandleReceivedCMSMessageEvent);
    
}
// EventConsumer(ConsumptionStrategy* pConsumptionStrategy);

// Destructor
EventConsumer::~EventConsumer()
{
    m_pMessageConsumer->ReceivedCMSMessageEvent -= Poco::Delegate<EventConsumer, std::pair<unsigned char*, unsigned long>*& >(this, &EventConsumer::HandleReceivedCMSMessageEvent);
}

// Helper(s)
void EventConsumer::Enqueue(google::protobuf::Message* pMessage)
{
    assert(pMessage);
    
    m_anEventQueue.lock();
    m_anEventQueue.push(pMessage);
    m_anEventQueue.unlock();
}

void EventConsumer::Enqueue(std::pair<unsigned char*, unsigned long>* pMessagePair)
{
    assert(pMessagePair);
    
    Message* pMessage = PairToMessage(pMessagePair);
    Enqueue(pMessage);
}

Message* EventConsumer::PairToMessage(std::pair<unsigned char*, unsigned long>* pMessagePair)
{
    using namespace gameevent;
    
    assert(pMessagePair);

    Message* pMessage = m_anEntityGameEventFactory.Create(pMessagePair);
    
    return pMessage;
}

// Method(s)
void EventConsumer::Consume()
{
    Message* pMessage = NULL;
    m_anEventQueue.lock();
    while (!m_anEventQueue.empty())
    {
        pMessage = m_anEventQueue.pop();
        EventConsumedEvent(this, pMessage);
    }
    m_anEventQueue.unlock();
}
// void Consume(google::protobuf::Message* pMessage)
//{
//      m_pConsumptionStrategy->Consume();
//}


// Event response
void EventConsumer::HandleReceivedCMSMessageEvent(const void* pSender, std::pair<unsigned char*, unsigned long>*& pMessagePair)
{
    Enqueue(pMessagePair);
}
