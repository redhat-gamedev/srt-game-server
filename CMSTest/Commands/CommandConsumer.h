#ifndef __CMSTest__CommandConsumer__
#define __CMSTest__CommandConsumer__

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

#include "SecurityCommandBufferFactory.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include "Poco/BasicEvent.h"
#include "Poco/Tuple.h"
#include <decaf/util/StlQueue.h>
#include <utility>

namespace cms
{
    class Message;
    class BytesMessage;
}
class MessageConsumer;


class CommandConsumer
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        MessageConsumer*                                                                m_pMessageConsumer;
        FactoryT<usx::geofactions::CommandBuffer, SecurityCommand_Dependencies>&        m_aSecurityCommandFactory;
        
        // Constructor
        _Dependencies(MessageConsumer* pMessageConsumer, FactoryT<usx::geofactions::CommandBuffer, SecurityCommand_Dependencies>& anSecurityCommandFactory);
        
        // Destructor
        ~_Dependencies();
    };

private:
protected:
    MessageConsumer*                                                                        m_pMessageConsumer;
    FactoryT<usx::geofactions::CommandBuffer, SecurityCommand_Dependencies>&                m_aSecurityCommandFactory;
    decaf::util::StlQueue<Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>* >    m_aTupleQueue;
    
    
    // Helper(s)
    void                                                Enqueue(Poco::Tuple<cms::BytesMessage*>* pTuple);
    std::pair<unsigned char*, unsigned long>*           MessageToPair(cms::BytesMessage* pBytesMessage);
    
    // Constructor(s)
    CommandConsumer(_Dependencies* pDependencies);
    
    // Destructor
    ~CommandConsumer();
    
public:
    // Event(s)
    Poco::BasicEvent<Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>*& >   CommandConsumedEvent;
    
    // Singleton
    static CommandConsumer& Instance(_Dependencies* pDependencies = NULL)//unsigned int uiCapacity)
    {
        static CommandConsumer  anCommandConsumer(pDependencies);
        return anCommandConsumer;
    }

    // Method(s)
    void Consume();
    
    // Event response
    void HandleReceivedCMSMessageEvent(const void* pSender, Poco::Tuple<cms::BytesMessage*>*& pTuple);
};

#endif /* defined(__CMSTest__CommandConsumer__) */
