//
//  SimpleAsyncProducer.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-28.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__SimpleAsyncProducer__
#define __CMSTest__SimpleAsyncProducer__


/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <decaf/lang/Runnable.h>
//#include <decaf/lang/Thread.h>
//#include <decaf/util/concurrent/CountDownLatch.h>
//#include <decaf/lang/Long.h>
//#include <decaf/util/Date.h>
//#include <activemq/core/ActiveMQConnectionFactory.h>
//#include <activemq/util/Config.h>
//#include <activemq/library/ActiveMQCPP.h>
//#include <cms/Connection.h>
//#include <cms/Session.h>
//#include <cms/TextMessage.h>
//#include <cms/BytesMessage.h>
//#include <cms/MapMessage.h>
//#include <cms/ExceptionListener.h>
//#include <cms/MessageListener.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <memory>

//using namespace activemq;
//using namespace activemq::core;
//using namespace decaf;
//using namespace decaf::lang;
//using namespace decaf::util;
//using namespace decaf::util::concurrent;
//using namespace cms;
//using namespace std;

namespace cms
{
    class Connection;
    class Session;
    class Destination;
    class MessageProducer;
}

class SimpleProducer :
    public decaf::lang::Runnable
{
private:
    
    cms::Connection*        connection;
    cms::Session*           session;
    cms::Destination*       destination;
    cms::MessageProducer*   producer;
    bool                    useTopic;
    bool                    clientAck;
    unsigned int            numMessages;
    std::string             brokerURI;
    std::string             destURI;
    
public:
    
    SimpleProducer( const std::string& brokerURI,
                   unsigned int numMessages,
                   const std::string& destURI,
                   bool useTopic = false,
                   bool clientAck = false );
    
    virtual ~SimpleProducer();
    
    void close();
    
    virtual void run();
    
private:
    
    void cleanup();
};

#endif /* defined(__CMSTest__SimpleAsyncProducer__) */
