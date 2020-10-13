#ifndef __CMSTest__MessageDispatcher__
#define __CMSTest__MessageDispatcher__

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
    decaf::util::StlQueue<std::pair<const unsigned char*, unsigned long>* >         m_aMessageQueue;
    SimpleAsyncProducer*                                                            m_pSimpleAsyncProducer;
    
    // Helper(s)
    void                                                Enqueue(google::protobuf::Message* pMessage);
    void                                                Enqueue(std::pair<const unsigned char*, unsigned long>* pMessagePair);
    std::pair<const unsigned char*, unsigned long>*     MessageToPair(google::protobuf::Message* pMessage);
    
    // Constructor
    MessageDispatcher(_Dependencies* pDependencies);
    
    // Destructor
    ~MessageDispatcher();

public:
    // Singleton
    static MessageDispatcher& Instance(_Dependencies* pDependencies)//unsigned int uiCapacity)
    {
        static MessageDispatcher  theMessageDispatcher(pDependencies);
        return theMessageDispatcher;
    }
    
    // Method(s)
    // Dispatches all the messages it has received to the network
    // via the configured simple async producer
    void Dispatch();
    
    // EventDispatcher event response
    void HandleEventDispatchedEvent(const void* pSender, google::protobuf::Message*& pEventMessage);
};

#endif /* defined(__CMSTest__MessageDispatcher__) */
