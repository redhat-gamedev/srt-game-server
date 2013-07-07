//
//  EventDispatcherFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__EventDispatcherFactory__
#define __CMSTest__EventDispatcherFactory__

#include "EventDispatcher.h"
#include "../Shared/FactoryT.h"


class EventDispatcherFactory :
    public FactoryT<EventDispatcher, EventDispatcher::_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    EventDispatcherFactory() {};
    
    // Destructor(s)
    ~EventDispatcherFactory() {};
    
public:
    // Singleton
    static EventDispatcherFactory& Instance()//unsigned int uiCapacity)
    {
        static EventDispatcherFactory  aEventDispatcherFactory;
        return aEventDispatcherFactory;
    }
    
    // Method(s)
    //void Destroy(EventDispatcher*& pEventDispatcher);
};

#endif /* defined(__CMSTest__EventDispatcherFactory__) */
