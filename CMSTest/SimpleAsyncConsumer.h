//
//  SimpleAsyncConsumer.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-10-28.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__SimpleAsyncConsumer__
#define __CMSTest__SimpleAsyncConsumer__


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

#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <decaf/net/URI.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;

////////////////////////////////////////////////////////////////////////////////
class SimpleAsyncConsumer :
    public ExceptionListener,
    public MessageListener,
    public DefaultTransportListener
{
private:
    
    Connection*         connection;
    Session*            session;
    Destination*        destination;
    MessageConsumer*    consumer;
    bool                useTopic;
    bool                clientAck;
    std::string         brokerURI;
    std::string         destURI;
    
public:
    
    SimpleAsyncConsumer(const std::string& brokerURI,
                        const std::string& destURI,
                        bool useTopic = false,
                        bool clientAck = false);
    
    virtual ~SimpleAsyncConsumer();
    
    void close();
    
    void runConsumer();
    
    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage( const Message* message );
    
    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException( const CMSException& ex AMQCPP_UNUSED );
    
    virtual void transportInterrupted();
    
    virtual void transportResumed();
    
private:
    
    void cleanup();
};


#endif /* defined(__CMSTest__SimpleAsyncConsumer__) */
