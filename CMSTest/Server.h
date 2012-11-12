//
//  Server.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Server__
#define __CMSTest__Server__

#include "decaf/util/StlQueue.h"
//#include "decaf/lang/Thread.h"
#include <string>

namespace decaf
{
    namespace lang
    {
        class Thread;        
    }
}
class SimpleProducer;
class SimpleAsyncConsumer;
class B2DWorld;

using namespace decaf::lang;
using namespace decaf::util;


class Server
{
// Class
private:
    
protected:

public:
    static StlQueue<std::string>      s_ProducerQueue;
    static StlQueue<std::string>      s_ConsumerQueue;
    
// Instance
private:
    
protected:
    SimpleProducer*         producer;
    Thread*                 pSimpleProducerThread;
    SimpleAsyncConsumer*    consumer;
    B2DWorld*               m_pB2DWorld;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
public:
    // Constructor(s)
    Server();
    
    // Destructor(s)
    ~Server();
    
    // Method(s)
    void Run();
    
};


#endif /* defined(__CMSTest__Server__) */
