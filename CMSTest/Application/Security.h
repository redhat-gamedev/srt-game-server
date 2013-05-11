//
//  Security.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Security__
#define __CMSTest__Security__

#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "../Game/Player.h"
#include "../Shared/PublisherT.cpp"
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


class Security :
    public cms::MessageListener,
    public cms::AsyncCallback,
    public Player::ICallbacks
{
public:
    class ICallbacks
    {
    public:
        virtual void OnSecurityRequestJoin(std::string& strUUID) {};
        virtual void OnSecurityRequestLeave(std::string& strUUID) {};
        virtual void OnSecurityHasJoined(const std::string& strUUID) {};
        virtual void OnSecurityHasLeft(const std::string& strUUID) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnSecurityRequestJoin(std::string& strUUID);
        virtual void OnSecurityRequestLeave(std::string& strUUID);
        virtual void OnSecurityHasJoined(const std::string& strUUID);
        virtual void OnSecurityHasLeft(const std::string& strUUID);
    };
    
    std::map<std::string, std::string>        m_mapUUIDToSimpleAsyncProducers;
    
public:
    static _Publisher               Publisher;
    
protected:
    SimpleAsyncConsumer*        m_pSimpleAsyncConsumer;
    SimpleProducer*             m_pSimpleAsyncProducer;
    
public:
    // Constructor(s)
    Security();
    
    // Destructor
    ~Security();
    
    // Method(s)
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
    
    // Player::ICallbacks implementation
    void OnPlayerCreated(const std::string& strUUID);
    void OnPlayerDestroyed(const std::string& strUUID);
    
    // cms::AsyncCallback implementation
    void onSuccess();
    void onException(const cms::CMSException& aCMSException);
};

#endif /* defined(__CMSTest__Security__) */
