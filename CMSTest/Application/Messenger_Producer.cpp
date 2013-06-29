//
//  Messenger_Producer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger_Producer.h"
#include "SimpleAsyncProducer.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include <cms/CMSException.h>
#include <google/protobuf/message.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <assert.h>

using namespace decaf::lang;
using namespace cms;


// Constructor(s)
Messenger::_Producer::_Producer() :
    m_pSimpleProducer(NULL),
    m_pProducerSerialDispatchQueue(NULL)//,
//    m_pThread(NULL)
//    m_pProducerDispatchTimer(NULL)
{

}

// Destructor(s)
Messenger::_Producer::~_Producer()
{

}

// Helper(s)
void Messenger::_Producer::Setup(std::string& strBrokerURI, std::string& strDestinationURI)
{
//    std::string     strThreadName = strDestinationURI + "-Thread";
    std::string     strDispatchQueueName = strDestinationURI + "-DispatchQueue";
    
    std::cout << "Starting the activemq simple producer" << std::endl;
    m_pSimpleProducer = new SimpleProducer(strBrokerURI, strDestinationURI, true);
    m_pProducerSerialDispatchQueue = new xdispatch::queue(strDispatchQueueName.c_str());
    
    //std::cout << "Starting the producer dispatch timer" << std::endl;
    //m_pProducerDispatchTimer = new xdispatch::timer(5 * NSEC_PER_MSEC, *m_pProducerSerialDispatchQueue);
    //m_pProducerDispatchTimer->start();
    
//    std::cout << "Starting " << strThreadName << std::endl;
//    m_pThread = new decaf::lang::Thread(this, strThreadName);
//    m_pThread->start();
}

void Messenger::_Producer::Teardown()
{
//    delete m_pThread;
//    m_pThread = NULL;

    //delete m_pProducerDispatchTimer;
    //m_pProducerDispatchTimer = NULL;
    
    delete m_pProducerSerialDispatchQueue;
    m_pProducerSerialDispatchQueue = NULL;
    
    m_pSimpleProducer->close();
    delete m_pSimpleProducer;
    m_pSimpleProducer = NULL;
}

// Method(s)
void Messenger::_Producer::Enqueue(::google::protobuf::Message* pMessage)
{
    assert(pMessage);
    
    m_aMessageQueue.lock();
    m_aMessageQueue.push(pMessage);
    m_aMessageQueue.unlock();
}

void Messenger::_Producer::SendUpdate(::google::protobuf::Message* pMessage)
{
    //assert(pMessage);
    //assert(pMessage->IsInitialized());
    
    using namespace std;
    using namespace gameevent;
    
    if (NULL == pMessage)
    {
        //printf("Messenger::_Producer::SendUpdate bailing on NULL pMessage");
        return;
    }
    
    string strPBBuffer = "";
    
    try
    {
        GameEvent* pGameEvent = static_cast<GameEvent*>(pMessage);
        //EntityGameEvent* pEntityGameEvent = pGameEvent->entitygameevent();
        const EntityGameEvent& anEntityGameEvent = pGameEvent->entitygameevent();
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
        const char* pucText = strPBBuffer.c_str();
        unsigned long ulLength = strPBBuffer.length();
        if (ulLength > 0)
        {
            m_pSimpleProducer->Send((const unsigned char*)pucText, (int)ulLength);
        }
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

void Messenger::_Producer::SendUpdates()
{
//    while (true)
//    {
        m_pProducerSerialDispatchQueue->sync([=]
        {
            m_aMessageQueue.lock();
            ::google::protobuf::Message* pMessage = m_aMessageQueue.pop();
            m_aMessageQueue.unlock();
            if (pMessage)
            {
                SendUpdate(pMessage);
                pMessage->Clear();
 //                delete pPbWorldDefault; // TODO: remove memory thrash
 //                pPbWorldDefault = NULL;
            }            
        });
        //decaf::lang::Thread::currentThread()->sleep(5);
//    }
}

//void Messenger::_Producer::run()
//{
//    SendUpdates();
//}

void Messenger::_Producer::ProcessEnqueuedMessages()
{
    //m_pProducerSerialDispatchQueue->sync([=]
    //{
    ::google::protobuf::Message* pMessage = NULL;
    
    try
    {
        m_aMessageQueue.lock();
        std::vector<::google::protobuf::Message*> vecMessage = m_aMessageQueue.toArray();
        m_aMessageQueue.clear();
        m_aMessageQueue.unlock();

        for(int i = 0; i < vecMessage.size(); ++i)
        {
            pMessage = vecMessage[i];
            if (pMessage)
            {
                SendUpdate(pMessage);
                pMessage->Clear();
            }
        }
    }
    catch (CMSException& e)
    {
        e.printStackTrace();
    }
    //});
}
