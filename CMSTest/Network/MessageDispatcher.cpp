//
//  MessageDispatcher.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "MessageDispatcher.h"
#include "SimpleAsyncProducer.h"
#include "../Events/EventDispatcher.h"
#include "../proto/GameEventBuffer.pb.h"
#include "Poco/Delegate.h"
#include <cms/CMSException.h>
#include <google/protobuf/message.h>
#include <string>
#include <assert.h>


// Constructor
MessageDispatcher::
_Dependencies::
_Dependencies(SimpleAsyncProducer* pSimpleAsyncProducer) :
    m_pSimpleAsyncProducer(pSimpleAsyncProducer)
{
    assert(m_pSimpleAsyncProducer);
}

// Destructor
MessageDispatcher::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
MessageDispatcher::MessageDispatcher(_Dependencies* pDependencies)
{
    assert(pDependencies);
    
    m_pSimpleAsyncProducer = pDependencies->m_pSimpleAsyncProducer;
    
    EventDispatcher& theEventDispatcher = EventDispatcher::Instance();
    theEventDispatcher.EventDispatchedEvent += Poco::Delegate<MessageDispatcher, google::protobuf::Message*&>(this, &MessageDispatcher::HandleEventDispatchedEvent);
    
    
    assert(m_pSimpleAsyncProducer);
}

// Destructor
MessageDispatcher::~MessageDispatcher()
{
    EventDispatcher& theEventDispatcher = EventDispatcher::Instance();
    theEventDispatcher.EventDispatchedEvent -= Poco::Delegate<MessageDispatcher, google::protobuf::Message*&>(this, &MessageDispatcher::HandleEventDispatchedEvent);
}

// Helper(s)
void MessageDispatcher::Enqueue(std::pair<const unsigned char*, unsigned long>* pMessagePair)
{
    m_aMessageQueue.lock();
    m_aMessageQueue.push(pMessagePair);
    m_aMessageQueue.unlock();
}

void MessageDispatcher::Enqueue(google::protobuf::Message* pEventMessage)
{
    assert(pEventMessage);
    
    std::pair<const unsigned char*, unsigned long>* pMessagePair = MessageToPair(pEventMessage);
    if (!pMessagePair)
    {
        return;
    }
        
    Enqueue(pMessagePair);
}

std::pair<const unsigned char*, unsigned long>* MessageDispatcher::MessageToPair(google::protobuf::Message* pMessage)
{
    assert(pMessage);

    using namespace std;
    using namespace usx::geofactions;
    
    pair<const unsigned char*, unsigned long>*      pMessagePair = NULL;
    const unsigned char*                            pucMessageBytes = NULL;
    
    if (NULL == pMessage)
    {
        return NULL;
    }
    
    string strPBBuffer = "";
    //GameEvent* pGameEvent = static_cast<GameEvent*>(pMessage);
    
    //EntityGameEvent* pEntityGameEvent = pGameEvent->entitygameevent();
    //const EntityGameEvent& anEntityGameEvent = pGameEvent->entitygameevent();
    //cout << hex << anEntityGameEvent.type() << endl;
    //        if (pEntityGameEvent)
    //{
    //uint64_t ui64Tag = anEntityGameEvent.entitytag();
    //bitset<sizeof(uint64_t)*8>    aBitSet(ui64Tag);
    //cout << hex << anEntityGameEvent.entitytag() << endl;
    //cout << aBitSet << endl;
    //}
    
    strPBBuffer.clear();
    pMessage->SerializeToString(&strPBBuffer);
    pMessage->Clear();
    //const char* pucText = strPBBuffer.c_str();
    unsigned long ulLength = strPBBuffer.length();    
    pucMessageBytes = new unsigned char[ulLength];
    memcpy((void*)pucMessageBytes, (const void*)strPBBuffer.c_str(), (size_t)(sizeof(char) * ulLength));
    pMessagePair = new pair<const unsigned char*, unsigned long>(pucMessageBytes, ulLength);

    return pMessagePair;
    
}
// Method(s)
// Dispatches all the messages it has received to the network
// via the configured simple async producer
void MessageDispatcher::Dispatch()
{
    m_aMessageQueue.lock();
    while (!m_aMessageQueue.empty())
    {
        try
        {
            std::pair<const unsigned char*, unsigned long>* pMessagePair = m_aMessageQueue.pop();
            if (pMessagePair->second > 0)
            {
                m_pSimpleAsyncProducer->Send(pMessagePair->first, (int)pMessagePair->second);
            }
        }
        catch ( cms::CMSException& e )
        {
            e.printStackTrace();
        }
    }
    m_aMessageQueue.unlock();
}

// EventDispatcher event response
void MessageDispatcher::HandleEventDispatchedEvent(const void* pSender, google::protobuf::Message*& pEventMessage)
{
    Enqueue(pEventMessage);
}