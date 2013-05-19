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
#include <decaf/lang/Thread.h>
#include <assert.h>

using namespace decaf::lang;
using namespace decaf::util::concurrent;
using namespace cms;


// Constructor(s)
Messenger::_Producer::_Producer() :
    m_pSimulationProducer(NULL),
    m_pProducerSerialDispatchQueue(NULL),
    m_pProducerDispatchTimer(NULL)
{
    Setup();
}

// Destructor(s)
Messenger::_Producer::~_Producer()
{
    Teardown();
}

// Helper(s)
void Messenger::_Producer::Setup()
{
    std::string     strWorldSimulationURI = "WORLD.SIMULATION";
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";

    std::cout << "Starting the activemq simple producer" << std::endl;    
    m_pSimulationProducer = new SimpleProducer(strBrokerURI, strWorldSimulationURI, true);
    m_pProducerSerialDispatchQueue = new xdispatch::queue("producer");
    
    std::cout << "Starting the producer dispatch timer" << std::endl;
    m_pProducerDispatchTimer = new xdispatch::timer(5 * NSEC_PER_MSEC, *m_pProducerSerialDispatchQueue);
    m_pProducerDispatchTimer->start();    
}

void Messenger::_Producer::Teardown()
{
    delete m_pProducerDispatchTimer;
    m_pProducerDispatchTimer = NULL;
    
    m_pSimulationProducer->close();
    delete m_pSimulationProducer;
    m_pSimulationProducer = NULL;
}

// Method(s)
void Messenger::_Producer::Enqueue(::box2d::PbWorld* pPbWorldDefault)
{
    assert(pPbWorldDefault);
    
    m_aSimulationUpdateQueue.lock();
    m_aSimulationUpdateQueue.push(pPbWorldDefault);
    m_aSimulationUpdateQueue.unlock();
}

void Messenger::_Producer::SendUpdate(::box2d::PbWorld* pPbWorldDefault)
{
    assert(pPbWorldDefault);
    
    static std::string strPBBuffer = "";
    
    try
    {
        strPBBuffer.clear();
        pPbWorldDefault->SerializeToString(&strPBBuffer);
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
            m_aSimulationUpdateQueue.lock();
            box2d::PbWorld*  pPbWorldDefault = m_aSimulationUpdateQueue.pop();
            m_aSimulationUpdateQueue.unlock();
            if (pPbWorldDefault)
            {
                SendUpdate(pPbWorldDefault);
                pPbWorldDefault->Clear();
 //                delete pPbWorldDefault; // TODO: remove memory thrash
 //                pPbWorldDefault = NULL;
            }
        });
        decaf::lang::Thread::currentThread()->sleep(5);
    }
}

// decaf::lang::Runnable implementation
void Messenger::_Producer::run()
{
    SendUpdates();
}