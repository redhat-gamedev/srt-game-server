#ifndef __SRT__MessageConsumer__
#define __SRT__MessageConsumer__

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

#include <proton/messaging_handler.hpp>
#include <Poco/BasicEvent.h>
#include <Poco/Tuple.h>
#include <utility>
#include <string>
#include <queue>
#include <mutex>
#include <thread>

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
class receiver;
class AEntity;


class MessageConsumer
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        receiver*                m_preceiver;
        
        // Constructor
        _Dependencies(receiver* preceiver);
        
        // Destructor
        ~_Dependencies();
    };
    
private:
protected:
    std::queue<Poco::Tuple<proton::message*>* >                       m_aTupleQueue;
    std::mutex                                                        m_aTupleQueueMutex;
    receiver*                                                         m_preceiver;
    std::thread*                                                      m_pReceiverThread;
    
    // Helper(s)
    void                                                Enqueue(proton::message* pBytesMessage);
    
    // Constructor
    MessageConsumer(_Dependencies* pDependencies);
    
    // Destructor
    ~MessageConsumer();
    
public:
    Poco::BasicEvent<Poco::Tuple<proton::message*>*& >              ReceivedCMSMessageEvent;
    
    // Singleton
    static MessageConsumer& Instance(_Dependencies* pDependencies)//unsigned int uiCapacity)
    {
        static MessageConsumer  theMessageConsumer(pDependencies);
        return theMessageConsumer;
    }
    
    // Method(s)
    void receive_thread(receiver& r);

    // Dispatches all the messages it has received to the network
    // via the configured simple async producer
    void Dispatch();
};

#endif /* defined(__SRT__MessageConsumer__) */
