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
#include "PublisherT.cpp"
#include <cms/MessageListener.h>
#include <string>
#include <map>

namespace cms
{
    class Message;
    class Destination;
}
class SimpleAsyncConsumer;
class SimpleAsyncProducer;


class Security :
    public cms::MessageListener
{
public:
    class ICallbacks
    {
    public:
        virtual void OnPlayerJoin(std::string strUUID) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnPlayerJoin(std::string strUUID);
    };
    
    std::map<std::string, const cms::Destination*>        m_mapUUIDToReplyDestinations;
    
public:
    static _Publisher               Publisher;
    
protected:
    SimpleAsyncConsumer*        m_pSimpleAsyncConsumer;
    SimpleAsyncProducer*        m_pSimpleAsyncProducer;
    
public:
    // Constructor(s)
    Security();
    
    // Destructor
    ~Security();
    
    // Method(s)
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
};

#endif /* defined(__CMSTest__Security__) */
