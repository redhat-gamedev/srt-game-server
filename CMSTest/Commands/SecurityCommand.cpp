//
//  SecurityCommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "SecurityCommand.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include "../Network/SimpleAsyncProducer.h"
#include <cms/Destination.h>
#include <cms/BytesMessage.h>
//#include <cms/TemporaryQueue.h>
#include <decaf/util/UUID.h>
#include <string>
#include <assert.h>


// Constructor
SecurityCommand::
_SecurityDependencies::
_SecurityDependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage) :
    ACommand::_Dependencies(pCommandBuffer, pBytesMessage)
{    
}

// Destructor
SecurityCommand::
_SecurityDependencies::
~_SecurityDependencies()
{
    
}


// Constructor
SecurityCommand::SecurityCommand(_SecurityDependencies& theDependencies) :
    ACommand(theDependencies)
{
    
}

// Destructor
SecurityCommand::~SecurityCommand()
{
    
}


// Constructor
JoinSecurityCommand::JoinSecurityCommand(_SecurityDependencies& theDependencies) :
    SecurityCommand(theDependencies)
{
    
}

// Destructor
JoinSecurityCommand::~JoinSecurityCommand()
{
    
}

// Method(s)
void JoinSecurityCommand::Execute()
{
    using namespace usx::geofactions;
    
    assert(m_pBytesMessage);
    assert(m_pCommandBuffer);
    
    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    std::string     strUUID = "";
    const SecurityCommandBuffer& aSecurityCommandBuffer = m_pCommandBuffer->securitycommandbuffer();
    
    decaf::util::UUID aNewUUID = decaf::util::UUID::randomUUID();
    strUUID = aNewUUID.toString();
    const cms::Destination* pReplyToDestination = m_pBytesMessage->getCMSReplyTo();
    assert(pReplyToDestination);
    
    // TODO: Make not super inefficient
    SimpleAsyncProducer* pSimpleAsyncProducer = new SimpleAsyncProducer(strBrokerURI, pReplyToDestination, false, true);
    pSimpleAsyncProducer->Send(strUUID);
    delete pSimpleAsyncProducer;
    
    ExecutedEvent(this, strUUID);
}


// Constructor
LeaveSecurityCommand::LeaveSecurityCommand(_SecurityDependencies& theDependencies) :
    SecurityCommand(theDependencies)
{
    //assert(m_pBytesMessage);
    //assert(m_pCommand);

    //const SecurityCommandBuffer& aSecurityCommandBuffer = pCommandBuffer->securitycommandbuffer();
    
    
}

// Destructor
LeaveSecurityCommand::~LeaveSecurityCommand()
{

}

// Method(s)
void LeaveSecurityCommand::Execute()
{
    using namespace usx::geofactions;
    
    assert(m_pCommandBuffer);
    
    const SecurityCommandBuffer& aSecurityCommandBuffer = m_pCommandBuffer->securitycommandbuffer();
    const LeaveSecurityCommandBuffer& aLeaveSecurityCommandBuffer = aSecurityCommandBuffer.leavesecuritycommandbuffer();
    const std::string& strUUID = aLeaveSecurityCommandBuffer.uuid();
    
    ExecutedEvent(this, strUUID);
}