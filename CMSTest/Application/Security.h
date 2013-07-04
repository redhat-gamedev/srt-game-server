//
//  Security.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Security__
#define __CMSTest__Security__

#include "../Game/AEntity.h"
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "Poco/BasicEvent.h"
#include <cms/MessageListener.h>
#include <cms/AsyncCallback.h>
#include <string>
#include <map>

namespace cms
{
    class Message;
    class Destination;
    class CMSException;
}
class SimpleAsyncConsumer;
class SimpleProducer;
class Player;


class Security :
    public cms::MessageListener,
    public cms::AsyncCallback
{
public:
    
    Poco::BasicEvent<int&>   IntEvent;

protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const std::string&>        RequestJoinEvent;
        Poco::BasicEvent<const std::string&>        RequestLeaveEvent;
        Poco::BasicEvent<const std::string&>        HasJoinedEvent;
        Poco::BasicEvent<const std::string&>        HasLeftEvent;
    };
    
    std::map<std::string, std::string>              m_mapUUIDToSimpleAsyncProducers;
    SimpleAsyncConsumer*                            m_pSimpleAsyncConsumer;
    SimpleProducer*                                 m_pSimpleAsyncProducer;
    
public:
    static _EventPublisher                          EventPublisher;

    // Constructor(s)
    Security();
    
    // Destructor
    ~Security();
    
    // Method(s)
    
    // Event Firing Method(s)
    void FireRequestJoinEvent(const std::string& strUUID);
    void FireRequestLeaveEvent(const std::string& strUUID);
    void FireHasJoinedEvent(const std::string& strUUID);
    void FireHasLeftEvent(const std::string& strUUID);
    
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
    
    // Player Event response
//    void OnPlayerCreated(const void* pSender, const AEntity::EType& anEntityType);
//    void OnPlayerDestroyed(const void* pSender, const AEntity::EType& anEntityType);
    void HandlePodCreatedEvent(const void* pSender, Player*& pPlayer);
    void HandlePodDestroyedEvent(const void* pSender, Player*& pPlayer);
    
    
    // cms::AsyncCallback implementation
    void onSuccess();
    void onException(const cms::CMSException& aCMSException);
};

#endif /* defined(__CMSTest__Security__) */
