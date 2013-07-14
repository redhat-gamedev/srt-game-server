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

//namespace google
//{
//    namespace protobuf
//    {
//        class Message;
//    }
//}

//class SecurityCommand_Dependencies;
//class AEntity;

//class IConsumptionStrategy
//{
//public:
//    virtual void Consume(google::protobuf::Message* pMessage) = 0;
//};
//
//template <class T> // where T == google::protobuf::Message*
//class ConsumptionStrategyT :
//    IConsumptionStrategy
//{
//public:
//    // Method(s)
//    void Consume(google::protobuf::Message* pMessage)
//    {
//        T   aTEvent;
//        
//        if (aTEvent.ParseFromArray(pucBodyBytes, iBodyBytes))
//        {
//            func[aTEvent.type()]();
//        }
//    }
//}
//
//class CommandMessageConsumptionStrategy :
//    public IConsumptionStrategy
//{
//public:
//    // Method(s)
//    void Consume(google::protobuf::Message* pMessage);
//};

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
    // ConsumptionStrategy*     pConsumptionStrategy;
    
    
    // Helper(s)
    void                                                Enqueue(google::protobuf::Message* pMessage);
    void                                                Enqueue(Poco::Tuple<cms::BytesMessage*>* pTuple);
    void                                                Enqueue(std::pair<unsigned char*, unsigned long>* pMessagePair);
    google::protobuf::Message*                          PairToMessage(std::pair<unsigned char*, unsigned long>* pMessagePair);
    std::pair<unsigned char*, unsigned long>*           MessageToPair(cms::BytesMessage* pBytesMessage);
    
    
    // Constructor(s)
    CommandConsumer(_Dependencies* pDependencies);
    // CommandConsumer(ConsumptionStrategy* pConsumptionStrategy);
    
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
