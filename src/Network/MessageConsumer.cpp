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

#include "MessageConsumer.h"
#include "receiver.h"
#include "../Logging/loguru.hpp"
#include <google/protobuf/message.h>
#include <string.h>
#include <string>
#include <assert.h>
#include <iomanip>
#include <iostream>


// Constructor
MessageConsumer::
_Dependencies::
_Dependencies(receiver* preceiver) :
    m_preceiver(preceiver)
{
    assert(m_preceiver);
}

// Destructor
MessageConsumer::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
MessageConsumer::MessageConsumer(_Dependencies* pDependencies)
{
    assert(pDependencies);

    m_preceiver = pDependencies->m_preceiver;
    
    assert(m_preceiver);

    // TODO: Proton TESTME -> kick off the receiver thread in the MessageConsumer
    m_pReceiverThread = new std::thread([&]() { receive_thread(*m_preceiver); });
}

// Destructor
MessageConsumer::~MessageConsumer()
{
    m_pReceiverThread->join();
    delete m_pReceiverThread;
    m_pReceiverThread = NULL;

    m_preceiver->close();
    delete m_preceiver;
    m_preceiver = NULL;
}

// Helper(s)
void MessageConsumer::Enqueue(proton::message* pBytesMessage)
{
    assert(pBytesMessage);
    
    Poco::Tuple<proton::message*>*    pTuple = new Poco::Tuple<proton::message*>(pBytesMessage);
    m_aTupleQueueMutex.lock();
    m_aTupleQueue.push(pTuple);
    m_aTupleQueueMutex.unlock();
}

// Method(s)
void MessageConsumer::receive_thread(receiver& r) {
    std::mutex out_lock;
    #define OUT(x) do { std::lock_guard<std::mutex> l(out_lock); x; } while (false)

    try {
        auto id = std::this_thread::get_id();
        int n = 0;
        // atomically check and decrement remaining *before* receiving.
        // If it is 0 or less then return, as there are no more
        // messages to receive so calling r.receive() would block forever.
        while (true) {
            auto m = r.receive();
            // TODO: Proton TESTME -> does this do a deep copy? if so who deletes it and when?
            proton::message* pMessage = new proton::message(m);
            Enqueue(pMessage);
//            OUT(std::cout << id << " received \"" << m.body() << '"' << std::endl);
        }
//        OUT(std::cout << id << " received " << n << " messages" << std::endl);
    } catch (const closed&) {}
}

// Dispatches all the messages it has received from the network
// via the configured simple async consumer
void MessageConsumer::Dispatch()
{
    // TODO: Used ScopedLock (?)
    try
    {
        m_aTupleQueueMutex.lock();
        while (!m_aTupleQueue.empty())
        {
            Poco::Tuple<proton::message*>*  pTuple = m_aTupleQueue.front();
            m_aTupleQueue.pop();
            ReceivedCMSMessageEvent(this, pTuple);
        }
        m_aTupleQueueMutex.unlock();
    }
    catch ( std::exception& e )
    {
        LOG_F(INFO, e.what());
    }
}
