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
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"
//#include "../../../ThirdParty/xdispatch/include/xdispatch/timer.h"
#include <decaf/util/StlQueue.h>
#include <decaf/lang/Runnable.h>


class SimpleProducer;
namespace google
{
    namespace protobuf
    {
        class Message;
    }
}


class Messenger::_Producer :
    decaf::lang::Runnable
{
    friend class Messenger;
    
private:
    
protected:
    SimpleProducer*                                         m_pSimpleProducer;
    xdispatch::queue*                                       m_pProducerSerialDispatchQueue;
//    xdispatch::timer*                                       m_pProducerDispatchTimer;
    decaf::util::StlQueue<::google::protobuf::Message*>     m_aMessageQueue;
    decaf::lang::Thread*                                    m_pThread;
 
    // Helper(s)
    void Setup(std::string& strBrokerURI, std::string& strDestinationURI);
    void Teardown();
    
public:
    // Constructor(s)
    _Producer();
    
    // Destructor(s)
    ~_Producer();
    
    // Method(s)
    void Enqueue(::google::protobuf::Message* pMessage);
    void SendUpdate(::google::protobuf::Message* pMessage);
    void SendUpdates();
    
    // decaf::lang::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Messenger_Producer__) */
