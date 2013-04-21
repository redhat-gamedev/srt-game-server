//
//  Heartbeat.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Heartbeat__
#define __CMSTest__Heartbeat__

#include "../Shared/PublisherT.cpp"
#include <decaf/util/TimerTask.h>
#include <list>


class Heartbeat :
    public decaf::util::TimerTask
{
// Class
public:
    class ICallbacks
    {
    public:
        virtual void OnBeat(int iBeat) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnBeat(int iBeat);
    };
    
public:
    static _Publisher               Publisher;
    
private:
protected:
public:
    
    // Instance
private:
protected:
    
public:
    // Constructor(s)
    Heartbeat();
    
    // Destructor(s)
    ~Heartbeat();
    
    // decaf::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Heartbeat__) */
