#ifndef __SRT__SimpleAsyncConsumer__
#define __SRT__SimpleAsyncConsumer__

//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <decaf/lang/Runnable.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <string>

namespace cms
{
    class Connection;
    class Session;
    class Destination;
    class MessageConsumer;
    class Message;
    class CMSException;
    //class MessageListener;
}


class SimpleAsyncConsumer :
    public cms::ExceptionListener,
    public cms::MessageListener,
    public activemq::transport::DefaultTransportListener
{
private:
    
    // Instance Data
    cms::Connection*        connection;
    cms::Session*           session;
    cms::Destination*       destination;
    cms::MessageConsumer*   consumer;
    bool                    useTopic;
    bool                    clientAck;
    std::string             brokerURI;
    std::string             destURI;
    
    // Helper(s)
    void cleanup();
    
public:
    
    // Constructor(s)
    SimpleAsyncConsumer(const std::string& brokerURI,
                        const std::string& destURI,
                        bool useTopic = false,
                        bool clientAck = false);
    
    // Destructor(s)
    virtual ~SimpleAsyncConsumer();

    // Method(s)
    // Called from the consumer since this class is a registered MessageListener.
    virtual void onMessage(const cms::Message* message);
    
    // If something bad happens you see it here as this class is also been
    // registered as an ExceptionListener with the connection.
    virtual void onException(const cms::CMSException& ex AMQCPP_UNUSED);
    virtual void transportInterrupted();
    virtual void transportResumed();

    // Function(s)
    void close();
    void runConsumer();
    
    void SetMessageListener(cms::MessageListener* pMessageListener);
};

#endif /* defined(__SRT__SimpleAsyncConsumer__) */
