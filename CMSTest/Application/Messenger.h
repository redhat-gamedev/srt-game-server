//
//  Messenger.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger__
#define __CMSTest__Messenger__

namespace decaf
{
    namespace lang
    {
        class Thread;
    }
    namespace util
    {
        class Timer;
    }
}


class Messenger
{
    friend class World;
private:
    
protected:
    class _Producer;
    class _Consumer;

    _Producer*                      m_pWorldProducer;
    decaf::lang::Thread*            m_pWorldProducerThread;
    
    // Helper(s)
    void Setup();
    void Teardown();
    
public:
    static const _Producer*    Producer;
    static const _Consumer*    Consumer;
    
    // Constructor(s)
    Messenger();
    
    // Destructor(s)
    ~Messenger();

};

#endif /* defined(__CMSTest__Messenger__) */
