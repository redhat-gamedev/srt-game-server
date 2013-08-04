//
//  RawInputCommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "RawInputCommand.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/RawInputCommandBuffer.pb.h"
#include <cms/BytesMessage.h>
#include <assert.h>


// Constructor
RawInputCommand::
_RawInputDependencies::
_RawInputDependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage) :
    ACommand::_Dependencies(pCommandBuffer, pBytesMessage)
{
}

// Destructor
RawInputCommand::
_RawInputDependencies::
~_RawInputDependencies()
{
    
}


// Constructor
RawInputCommand::RawInputCommand(_RawInputDependencies& theDependencies) :
    ACommand(theDependencies)
{
    
}

// Destructor
RawInputCommand::~RawInputCommand()
{
    
}


// Constructor
DualStickRawInputCommand::DualStickRawInputCommand(_RawInputDependencies& theDependencies) :
    RawInputCommand(theDependencies)
{
    
}

// Destructor
DualStickRawInputCommand::~DualStickRawInputCommand()
{
    
}

// Method(s)
void DualStickRawInputCommand::Execute()
{
    using namespace usx::geofactions;
    
    assert(m_pBytesMessage);
    assert(m_pCommandBuffer);
    
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    std::string     strUUID = "";
    const RawInputCommandBuffer& aRawInputCommandBuffer = m_pCommandBuffer->rawinputcommandbuffer();

    
    
    ExecutedEvent(this, strUUID);
}
