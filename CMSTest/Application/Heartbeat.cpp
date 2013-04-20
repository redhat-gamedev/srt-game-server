//
//  Heartbeat.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 12-11-12.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#include "Heartbeat.h"
#include <stdio.h>

Heartbeat::_Publisher                 Heartbeat::Publisher;


// Constructor(s)
/*
 B2DWorld.h::_Publisher::_Publisher()
 {
 
 }
 */

// Destructor
/*
 B2DWorld.h::_Publisher::~_Publisher()
 {
 
 }
 */

// Method(s)
void Heartbeat::_Publisher::OnBeat(int iBeat)
{
    ICallbacks* pObjToCallback = NULL;
    
    Clone(m_listSubscribersSwap);
    while(!m_listSubscribersSwap.empty())
    {
        pObjToCallback = m_listSubscribersSwap.front();
        m_listSubscribersSwap.pop_front();
        assert(pObjToCallback);
        pObjToCallback->OnBeat(iBeat);
    }
}

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

// Method(s)
void Heartbeat::run()
{
    static int iBeat = 0;
    //printf("%i", i);
    Publisher.OnBeat(iBeat);
    ++iBeat;
}