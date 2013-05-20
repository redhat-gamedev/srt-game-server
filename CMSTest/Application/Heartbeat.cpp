//
//  Heartbeat.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Heartbeat.h"
#include <stdio.h>

Heartbeat::_EventPublisher              Heartbeat::EventPublisher;


// Constructor(s)
Heartbeat::Heartbeat()
{
    
}

// Destructor(s)
Heartbeat::~Heartbeat()
{
    int i = 0;
    ++i;
}

// Event Firing Method(s)
void Heartbeat::FireBeatEvent(const int& iBeat)
{
    EventPublisher.BeatEvent(this, iBeat);
}

// decaf::Runnable implementation
void Heartbeat::run()
{
    static int iBeat = 0;
    //printf("%i", i);
    FireBeatEvent(iBeat);
    ++iBeat;
}