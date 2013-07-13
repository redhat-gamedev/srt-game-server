//
//  SecurityCommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "SecurityCommand.h"
#include "../Shared/SimpleAsyncProducer.h"
#include <cms/Destination.h>
//#include <cms/TemporaryQueue.h>
#include <decaf/util/UUID.h>
#include <string>
#include <assert.h>


// Constructor
SecurityCommand::
_SecurityDependencies::
_SecurityDependencies(command::Command& aCommand, const cms::Destination* pReplyToDestination) :
    m_pReplyToDestination(pReplyToDestination),
    ACommand::_Dependencies(aCommand)
{
    assert(m_pReplyToDestination);
    
}

// Destructor
SecurityCommand::
_SecurityDependencies::
~_SecurityDependencies()
{
    
}


// Constructor
SecurityCommand::SecurityCommand(_SecurityDependencies& theDependencies) :
    m_pReplyToDestination(theDependencies.m_pReplyToDestination),
    ACommand(theDependencies)
{
    
}

// Destructor
SecurityCommand::~SecurityCommand()
{
    
}

// Method(s)
void SecurityCommand::Execute()
{
    // Join stuff
    // don't forget to ->clone() the reply to destination if lifetime is impt
//    const cms::Destination* pDestination = pBytesMessage->getCMSReplyTo();

    assert(m_pReplyToDestination);

    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    
    decaf::util::UUID aNewUUID = decaf::util::UUID::randomUUID();
    std::string strUUID = aNewUUID.toString();

    // TODO: Make not super inefficient
    SimpleAsyncProducer* pSimpleAsyncProducer = new SimpleAsyncProducer(strBrokerURI, m_pReplyToDestination, false, true);
    pSimpleAsyncProducer->Send(strUUID);
    delete pSimpleAsyncProducer;
}


//// Constructor
//JoinSecurityCommand::JoinSecurityCommand(_Dependencies& theDependencies) :
//    SecurityCommand(theDependencies)
//{
//    
//}
//
//// Destructor
//JoinSecurityCommand::JoinSecurityCommand()
//{
//    
//}
//
//// Method(s)
//void JoinSecurityCommand::Execute()
//{
//}
