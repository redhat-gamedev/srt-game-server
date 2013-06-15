//
//  Messenger_Consumer.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger_Consumer__
#define __CMSTest__Messenger_Consumer__

#include "Messenger.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>
#include <cms/MessageListener.h>
#include <string>
#include <stdint.h>

namespace cms
{
    class Message;
    class BytesMessage;
}
namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
class SimpleAsyncConsumer;
class AEntity;


class Messenger::_Consumer :
    public cms::MessageListener
{
        friend class Messenger;
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const AEntity&>        ReceivedCreateEntityRequest;
        Poco::BasicEvent<const AEntity&>        ReceivedDestroyEntityRequest;
    };
    
private:
    
protected:
    SimpleAsyncConsumer*                                            m_pSimpleAsyncConsumer;
    decaf::util::StlQueue<std::pair<int, unsigned char*> >          m_aMessageQueue;
    
    // Helper(s)
    void Setup(std::string& strBrokerURI, std::string& strDestinationURI);
    void Teardown();
    
public:
    static _EventPublisher                          EventPublisher;
    
    // Constructor(s)
    _Consumer();
    
    // Destructor(s)
    ~_Consumer();
    
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
    
    void ProcessReceivedMessages();
};

#endif /* defined(__CMSTest__Messenger_Consumer__) */
