//
//  Input.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-09.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Input__
#define __CMSTest__Input__

#include <cms/MessageListener.h>

namespace cms
{
    class Message;
}
class SimpleAsyncConsumer;


class Input :
    public cms::MessageListener
{
private:
    
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
