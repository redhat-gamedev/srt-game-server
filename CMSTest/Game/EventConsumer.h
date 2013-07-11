//
//  EventConsumer.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-10.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__EventConsumer__
#define __CMSTest__EventConsumer__

#include "EntityGameEventFactory.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>
#include <utility>

//namespace google
//{
//    namespace protobuf
//    {
//        class Message;
//    }
//}
class MessageConsumer;
//class EntityGameEvent_Dependencies;
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
//class GameEventMessageConsumptionStrategy :
//    public IConsumptionStrategy
//{
//public:
//    // Method(s)
//    void Consume(google::protobuf::Message* pMessage);
//};

class EventConsumer
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        MessageConsumer*                                                        m_pMessageConsumer;
        FactoryT<gameevent::GameEvent, EntityGameEvent_Dependencies>&           m_anEntityGameEventFactory;
        
        // Constructor
        _Dependencies(MessageConsumer* pMessageConsumer, FactoryT<gameevent::GameEvent, EntityGameEvent_Dependencies>& anEntityGameEventFactory);
        
        // Destructor
        ~_Dependencies();
    };

private:
protected:
    decaf::util::StlQueue<google::protobuf::Message*>                       m_anEventQueue;
    MessageConsumer*                                                        m_pMessageConsumer;
    FactoryT<gameevent::GameEvent, EntityGameEvent_Dependencies>&           m_anEntityGameEventFactory;
    
    // Helper(s)
    void                                                Enqueue(google::protobuf::Message* pMessage);
    void                                                Enqueue(std::pair<unsigned char*, unsigned long>* pMessagePair);
    google::protobuf::Message*                          PairToMessage(std::pair<unsigned char*, unsigned long>* pMessagePair);
    
    // ConsumptionStrategy*     pConsumptionStrategy;
    
    
    // Constructor(s)
    // EventConsumer(ConsumptionStrategy* pConsumptionStrategy);
    EventConsumer(_Dependencies* pDependencies);
    
    // Destructor
    ~EventConsumer();
    
public:
    // Event(s)
    Poco::BasicEvent<google::protobuf::Message*&>   EventConsumedEvent;
    
    // Singleton
    static EventConsumer& Instance(_Dependencies* pDependencies = NULL)//unsigned int uiCapacity)
    {
        static EventConsumer  anEventConsumer(pDependencies);
        return anEventConsumer;
    }

    // Method(s)
    void Consume();
    
    // Event response
    void HandleReceivedCMSMessageEvent(const void* pSender, std::pair<unsigned char*, unsigned long>*& pMessagePair);
};

#endif /* defined(__CMSTest__EventConsumer__) */
