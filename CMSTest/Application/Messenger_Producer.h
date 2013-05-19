//
//  Messenger_Producer.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger_Producer__
#define __CMSTest__Messenger_Producer__

#include "Messenger.h"
#include "../Proto/box2d.pb.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/timer.h"
//#include <decaf/lang/Runnable.h>
#include <decaf/util/StlQueue.h>
#include <string>

class SimpleProducer;


class Messenger::_Producer// :
//    public decaf::lang::Runnable
{
    friend class Messenger;
    
private:
    
protected:
    SimpleProducer*                             m_pSimulationProducer;
    
    xdispatch::queue*                           m_pProducerSerialDispatchQueue;
    xdispatch::timer*                           m_pProducerDispatchTimer;
    
    decaf::util::StlQueue<::box2d::PbWorld*>    m_aSimulationUpdateQueue;
    
    //decaf::lang::Thread*                        m_pProducerThread;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
public:
    // Constructor(s)
    _Producer();
    
    // Destructor(s)
    ~_Producer();
    
    // Method(s)
    void Enqueue(::box2d::PbWorld* pPbWorldDefault);
    void SendUpdate(::box2d::PbWorld* pPbWorldDefault);
    void SendUpdates();
    
    // decaf::lang::Runnable implementation
    //void run();
};

#endif /* defined(__CMSTest__Messenger_Producer__) */
