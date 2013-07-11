//
//  Messenger.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-19.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "Messenger.h"
#include "Messenger_Consumer.h"
#include "../Game/AEntity.h"
#include "../Game/Player.h"
#include "../Game/PodFactory.h"
#include "../Game/Bullet.h"
#include "../Game/BulletFactory.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include "Poco/Delegate.h"
#include "Poco/FunctionDelegate.h"
//#include <decaf/lang/Thread.h>
#include <string>
#include <iostream>
//#include <bitset>
#include <assert.h>

Messenger::_Consumer            Messenger::Consumer;
const std::string               Messenger::BrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";

// Constructor(s)
Messenger::Messenger()// :
    //s_pThread(NULL)
{

}

// Destructor(s)
Messenger::~Messenger()
{

}

// Class function(s)
void Messenger::Setup()
{
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp";
    //std::string     strWorldSimulationDestinationURI = "WORLD.SIMULATION";
    std::string     strGameEventInDestinationURI = "GAME.EVENT.IN";
    std::string     strGameEventOutDestinationURI = "GAME.EVENT.OUT";
    std::string     strThreadName = "MessengerThread";

    // Game Event
    Consumer.Setup(strBrokerURI, strGameEventInDestinationURI);
    
//    std::cout << "Starting " << strThreadName << std::endl;
//    s_pThread = new decaf::lang::Thread(this, strThreadName);
//    s_pThread->start();
}

void Messenger::Teardown()
{
//    delete s_pThread;
//    s_pThread = NULL;

    Consumer.Teardown();
}

void Messenger::SendUpdates()
{
}
