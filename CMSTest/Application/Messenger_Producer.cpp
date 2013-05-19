//
//  Messenger_Producer.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger_Producer.h"
#include "SimpleAsyncProducer.h"
#include <cms/CMSException.h>
#include <google/protobuf/message.h>
#include <assert.h>

using namespace decaf::lang;
using namespace cms;


// Constructor(s)
Messenger::_Producer::_Producer() :
    m_pSimulationProducer(NULL),
    m_pProducerSerialDispatchQueue(NULL),
    m_pProducerDispatchTimer(NULL)
{

}

// Destructor(s)
Messenger::_Producer::~_Producer()
{

}

// Helper(s)
void Messenger::_Producer::Setup()
{
    std::string     strWorldSimulationURI = "WORLD.SIMULATION";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    std::string     strWorldProducerThreadName = "WorldProducerThread";
    //std::string     strWorldProducerQueueName = "WorldProducerQueue";
    const char*     pszWorldProducerQueueName = "WorldProducerQueue";
    //const char*     pszWorldProducerQueueName = &szWorldProducerQueueName;
    
    std::cout << "Starting the activemq simple producer" << std::endl;
    m_pSimulationProducer = new SimpleProducer(strBrokerURI, strWorldSimulationURI, true);
    //m_pProducerSerialDispatchQueue = new xdispatch::queue("WorldProducerQueue");
    m_pProducerSerialDispatchQueue = new xdispatch::queue(pszWorldProducerQueueName);
    
    //std::cout << "Starting the producer dispatch timer" << std::endl;
    //m_pProducerDispatchTimer = new xdispatch::timer(5 * NSEC_PER_MSEC, *m_pProducerSerialDispatchQueue);
    //m_pProducerDispatchTimer->start();
}

void Messenger::_Producer::Teardown()
{
    //delete m_pProducerDispatchTimer;
    //m_pProducerDispatchTimer = NULL;
    
    delete m_pProducerSerialDispatchQueue;
    m_pProducerSerialDispatchQueue = NULL;
    
    m_pSimulationProducer->close();
    delete m_pSimulationProducer;
    m_pSimulationProducer = NULL;
}

// Method(s)
void Messenger::_Producer::Enqueue(::box2d::PbWorld* pPbWorld)
{
    assert(pPbWorld);
    
    m_aMessageQueue.lock();
    m_aMessageQueue.push(pPbWorld);
    m_aMessageQueue.unlock();
}

//void Messenger::_Producer::SendUpdate(::box2d::PbWorld* pPbWorld)
void Messenger::_Producer::SendUpdate(::google::protobuf::Message* pMessage)
{
//    assert(pPbWorld);
    assert(pMessage);
    
    static std::string strPBBuffer = "";
    
    try
    {
//        m_aMessageQueue.lock();
//        ::google::protobuf::Message* pMessage = m_aMessageQueue.pop();
//        pMessage->SerializeToString(&strPBBuffer);
//        m_aMessageQueue.unlock();
        
        strPBBuffer.clear();
        //pPbWorld->SerializeToString(&strPBBuffer);
        pMessage->SerializeToString(&strPBBuffer);
        const char* pucText = strPBBuffer.c_str();
        unsigned long ulLength = strPBBuffer.length();
        if (ulLength > 0)
        {
            m_pSimulationProducer->Send((const unsigned char*)pucText, (int)ulLength);
        }
    }
    catch ( CMSException& e )
    {
        e.printStackTrace();
    }
}

void Messenger::_Producer::SendUpdates()
{
    while (true)
    {
        m_pProducerSerialDispatchQueue->sync([=]
        {
            m_aMessageQueue.lock();
            //box2d::PbWorld*  pPbWorldDefault = m_aMessageQueue.pop();
            ::google::protobuf::Message* pMessage = m_aMessageQueue.pop();
            m_aMessageQueue.unlock();
            //if (pPbWorldDefault)
            if (pMessage)
            {
                //SendUpdate(pPbWorldDefault);
                SendUpdate(pMessage);
                //pPbWorldDefault->Clear();
                pMessage->Clear();
 //                delete pPbWorldDefault; // TODO: remove memory thrash
 //                pPbWorldDefault = NULL;
            }
        });
        decaf::lang::Thread::currentThread()->sleep(5);
    }
}
