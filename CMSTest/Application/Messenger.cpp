//
//  Messenger.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger.h"
#include "Messenger_Producer.h"
#include <decaf/lang/Thread.h>
#include <string.h>

Messenger::_Producer            Messenger::Producer;


// Constructor(s)
Messenger::Messenger()
{

}

// Destructor(s)
Messenger::~Messenger()
{

}

// Class function(s)
void Messenger::Setup()
{
    Producer.Setup();
}

void Messenger::Teardown()
{
    Producer.Teardown();
}

void Messenger::Send()
{
    Producer.SendUpdates();
}
