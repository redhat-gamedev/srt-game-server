//
//  Security.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Security__
#define __CMSTest__Security__

#include "DualStick.pb.h"
#include "box2d.pb.h"
#include "Player.h"
#include "PublisherT.cpp"
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
        virtual void OnSecurityJoin(std::string& strUUID) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnSecurityJoin(std::string& strUUID);
    };
    
    //std::map<std::string, const cms::Destination*>        m_mapUUIDToReplyDestinations;
    std::map<std::string, std::string>        m_mapUUIDToReplyDestinations;
    
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
    void OnPlayerCreated(std::string& strUUID);
    
    // cms::AsyncCallback implementation
    void onSuccess();
    void onException(const cms::CMSException& aCMSException);
};

#endif /* defined(__CMSTest__Security__) */
