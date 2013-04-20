//
//  Input.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Input__
#define __CMSTest__Input__

#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "../Shared/PublisherT.cpp"
#include <cms/MessageListener.h>
#include <string>
#include <list>

namespace cms
{
    class Message;
}
class SimpleAsyncConsumer;


class Input :
    public cms::MessageListener
{
public:
    class ICallbacks
    {
    public:
        virtual void OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnDualStick(const std::string& strUUID, const box2d::PbVec2& pbv2Move, const box2d::PbVec2& pbv2Shoot);
    };
    
public:
    static _Publisher               Publisher;
    
protected:
    SimpleAsyncConsumer*        m_pSimpleAsyncConsumer;
    
public:
    // Constructor(s)
    Input();
    
    // Destructor
    ~Input();
    
    // Method(s)
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
};

#endif /* defined(__CMSTest__Input__) */
