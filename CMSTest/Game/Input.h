//
//  Input.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Input__
#define __CMSTest__Input__
#if 0
#include "../Proto/DualStick.pb.h"
#include "../Proto/box2d.pb.h"
#include "Poco/BasicEvent.h"
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
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<DualStick::PbDualStick>     DualStickEvent;
    };

    SimpleAsyncConsumer*        m_pSimpleAsyncConsumer;

public:
    static _EventPublisher          EventPublisher;

    // Constructor(s)
    Input();
    
    // Destructor
    ~Input();
    
    // MessageListener implementation
    virtual void onMessage(const cms::Message* pMessage);
    
    // Event Firing Method(s)
    void FireDualStickEvent(DualStick::PbDualStick aPbDualStick);
};
#endif
#endif /* defined(__CMSTest__Input__) */
