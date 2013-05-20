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
    static _Producer    Producer;
    //static _Consumer    Consumer;
    
    // Class function(s)
    static void Setup();
    static void Teardown();
    static void Send();
};

#endif /* defined(__CMSTest__Messenger__) */
