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
    //b2Vec2          b2v2Move;
    //b2Vec2          b2v2Shoot;
    const RawInputCommandBuffer& aRawInputCommandBuffer = m_pCommandBuffer->rawinputcommandbuffer();
    const DualStickRawInputCommandBuffer& aDualStickRawInputCommandBuffer = aRawInputCommandBuffer.dualstickrawinputcommandbuffer();
    
    strUUID = aRawInputCommandBuffer.uuid();
    m_b2v2Move.x = aDualStickRawInputCommandBuffer.pbv2move().x();
    m_b2v2Move.y = aDualStickRawInputCommandBuffer.pbv2move().y();
    m_b2v2Shoot.x = aDualStickRawInputCommandBuffer.pbv2shoot().x();
    m_b2v2Shoot.y = aDualStickRawInputCommandBuffer.pbv2shoot().y();
    
    ExecutedEvent(this, strUUID);
    //ExecutedEvent(this, strUUID, b2v2Move, b2v2Shoot);
}
