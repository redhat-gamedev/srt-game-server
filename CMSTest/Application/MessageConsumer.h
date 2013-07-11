//
//  MessageConsumer.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-10.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__MessageConsumer__
#define __CMSTest__MessageConsumer__

#include "Poco/BasicEvent.h"
#include <cms/MessageListener.h>
#include <decaf/util/StlQueue.h>
#include <utility>
#include <string>

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


class MessageConsumer :
    cms::MessageListener
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        SimpleAsyncConsumer*                m_pSimpleAsyncConsumer;
        
        // Constructor
        _Dependencies(SimpleAsyncConsumer* pSimpleAsyncConsumer);
        
        // Destructor
        ~_Dependencies();
    };
    
private:
protected:
    decaf::util::StlQueue<std::pair<unsigned char*, unsigned long>* >         m_aMessageQueue;
    SimpleAsyncConsumer*                                                      m_pSimpleAsyncConsumer;
    
    // Helper(s)
    void                                                Enqueue(const cms::Message* pMessage);
    void                                                Enqueue(std::pair<unsigned char*, unsigned long>* pMessagePair);
    std::pair<unsigned char*, unsigned long>*           MessageToPair(const cms::Message* pMessage);
    
    // Constructor
    MessageConsumer(_Dependencies* pDependencies);
    
    // Destructor
    ~MessageConsumer();
    
public:
    Poco::BasicEvent<std::pair<unsigned char*, unsigned long>*& >              ReceivedCMSMessageEvent;
    
    // Singleton
    static MessageConsumer& Instance(_Dependencies* pDependencies)//unsigned int uiCapacity)
    {
        static MessageConsumer  theMessageConsumer(pDependencies);
        return theMessageConsumer;
    }
    
    // Method(s)
    // Dispatches all the messages it has received to the network
    // via the configured simple async producer
    void Dispatch();
    
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
};

#endif /* defined(__CMSTest__MessageConsumer__) */
