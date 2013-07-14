//
//  CommandConsumer.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-10.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__CommandConsumer__
#define __CMSTest__CommandConsumer__

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
    MessageConsumer*                                                        m_pMessageConsumer;
    FactoryT<usx::geofactions::CommandBuffer, SecurityCommand_Dependencies>&       m_aSecurityCommandFactory;
    decaf::util::StlQueue<Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>* >                       m_aTupleQueue;
    
    
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
