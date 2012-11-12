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

#include "B2DWorld.h"
#include "../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "decaf/lang/Runnable.h"
#include <string>

namespace cms
{
    class Connection;
    class Session;
    class Destination;
    class MessageProducer;
}


class SimpleProducer :
    public decaf::lang::Runnable,
    public B2DWorld::ICallbacks
{
private:
    
    // ActiveMQ-CPP
    cms::Connection*        connection;
    cms::Session*           session;
    cms::Destination*       destination;
    cms::MessageProducer*   producer;
    bool                    useTopic;
    bool                    clientAck;
    unsigned int            numMessages;
    std::string             brokerURI;
    std::string             destURI;
    
    // Helper(s)
    void cleanup();
    
public:

    // Constructor(s)
    SimpleProducer(const std::string& brokerURI,
                   unsigned int numMessages,
                   const std::string& destURI,
                   bool useTopic = false,
                   bool clientAck = false);
    
    // Destructor(s)
    virtual ~SimpleProducer();
    
    // Method(s)
    virtual void run();
    
    // Function(s)
    void close();
    
    // B2DWorld::ICallbacks implementation
    void OnB2DWorldUpdate(b2Vec2& b2vNewPosition, float32& fNewAngle);
};

#endif /* defined(__CMSTest__SimpleAsyncProducer__) */
