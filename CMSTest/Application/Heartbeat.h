//
//  Heartbeat.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Heartbeat__
#define __CMSTest__Heartbeat__

#include "Poco/BasicEvent.h"
#include <decaf/util/TimerTask.h>
#include <list>


class Heartbeat :
    public decaf::util::TimerTask
{
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const int&>     BeatEvent;
    };
    
public:
    static _EventPublisher              EventPublisher;

    // Constructor(s)
    Heartbeat();
    
    // Destructor(s)
    ~Heartbeat();
    
    // Event Firing Method(s)
    void FireBeatEvent(const int& iBeat);
    
    // decaf::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Heartbeat__) */
