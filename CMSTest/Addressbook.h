//
//  Addressbook.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Addressbook__
#define __CMSTest__Addressbook__

#include "decaf/util/TimerTask.h"
#include "addressbook.pb.h"
#include "PublisherT.cpp"
#include <list>


class Addressbook :
    public decaf::util::TimerTask
{
    // Class
public:
    class ICallbacks
    {
    public:
        virtual void OnPerson(tutorial::Person* person) {};
    };
    
protected:
    class _Publisher :
        public ICallbacks,
        public PublisherT<ICallbacks*>
    {
    protected:
        std::list<ICallbacks*>          m_listSubscribersSwap;
    public:
        virtual void OnPerson(tutorial::Person* person);
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
    Addressbook();
    
    // Destructor(s)
    ~Addressbook();
    
    // decaf::Runnable implementation
    void run();
};

#endif /* defined(__CMSTest__Addressbook__) */
