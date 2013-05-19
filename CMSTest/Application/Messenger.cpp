//
//  Messenger.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger.h"
#include "Messenger_Producer.h"
#include <decaf/lang/Thread.h>
#include <string.h>

//decaf::lang::Thread*            Messenger::m_pWorldProducerThread = NULL;
Messenger::_Producer            Messenger::Producer;


// Constructor(s)
Messenger::Messenger()// :
//    m_pWorldProducer(NULL),
    //m_pWorldProducerThread(NULL),
    //Producer(NULL)
{
//    Setup();
}

// Destructor(s)
Messenger::~Messenger()
{
//    Teardown();
}

// Helper(s)
void Messenger::Setup()
{
//    std::string     strWorldProducerName = "WorldProducerThread";
//    
//    std::cout << "Starting the world producer" << std::endl;
////    m_pWorldProducer = new _Producer();
////    m_pWorldProducerThread = new decaf::lang::Thread(m_pWorldProducer, strWorldProducerName);
//    m_pWorldProducerThread = new decaf::lang::Thread(&Producer, strWorldProducerName);
//    m_pWorldProducerThread->start();
}

void Messenger::Teardown()
{
//    delete m_pWorldProducerThread;
//    m_pWorldProducerThread = NULL;
    
//    delete m_pWorldProducer;
//    m_pWorldProducer = NULL;
}