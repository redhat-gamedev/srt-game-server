//
//  Messenger.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Messenger__
#define __CMSTest__Messenger__

#include <string>

class EntityData;


class Messenger
{
private:
    
protected:
    class _Producer;
    class _Consumer;

    static const std::string        BrokerURI;
    
    // Constructor(s)
    Messenger();
    
    // Destructor(s)
    ~Messenger();
    
public:
    // World Simulation
    static _Producer    Producer;
    
    // Game Event
    static _Producer    GameEventProducer;
    static _Consumer    Consumer;
    
    // Class function(s)
    static void Setup();
    static void Teardown();
    static void Send();
    
    // Player Event response
    static void OnPlayerCreated(const void* pSender, const EntityData& anEntityData);
    static void OnPlayerDestroyed(const void* pSender, const EntityData& anEntityData);
};

#endif /* defined(__CMSTest__Messenger__) */
