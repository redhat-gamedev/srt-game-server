//
//  MessageDispatcher.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__MessageDispatcher__
#define __CMSTest__MessageDispatcher__

#include <decaf/util/StlQueue.h>
#include <utility>

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
class SimpleAsyncProducer;


class MessageDispatcher
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        SimpleAsyncProducer*                m_pSimpleAsyncProducer;
        
        // Constructor
        _Dependencies(SimpleAsyncProducer* pSimpleAsyncProducer);
        
        // Destructor
        ~_Dependencies();
    };

private:
protected:
    decaf::util::StlQueue<std::pair<const unsigned char*, unsigned long>* >       m_aMessageQueue;
    SimpleAsyncProducer*                                                m_pSimpleAsyncProducer;
    
    // Helper(s)
    void                                    Enqueue(google::protobuf::Message* pMessage);
    void                                    Enqueue(std::pair<const unsigned char*, unsigned long>* pMessagePair);
    std::pair<const unsigned char*, unsigned long>*   MessageToPair(google::protobuf::Message* pMessage);
    
    // Constructor
    MessageDispatcher(_Dependencies& theDependencies);
    
    // Destructor
    ~MessageDispatcher();

public:
    // Singleton
    static MessageDispatcher& Instance(_Dependencies& theDependencies)//unsigned int uiCapacity)
    {
        static MessageDispatcher  aMessageDispatcher(theDependencies);
        return aMessageDispatcher;
    }
    
    // Method(s)
    // Dispatches all the messages it has received to the network
    // via the configured simple async producer
    void Dispatch();
    
    // EventDispatcher event response
    void HandleEventDispatchedEvent(const void* pSender, google::protobuf::Message*& pEventMessage);
};

#endif /* defined(__CMSTest__MessageDispatcher__) */
