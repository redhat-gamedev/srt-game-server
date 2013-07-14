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
#include "../Shared/SimpleAsyncProducer.h"
#include <cms/Destination.h>
#include <cms/BytesMessage.h>
//#include <cms/TemporaryQueue.h>
#include <decaf/util/UUID.h>
#include <string>
#include <assert.h>


// Constructor
SecurityCommand::
_SecurityDependencies::
_SecurityDependencies(usx::geofactions::CommandBuffer* pCommand, const cms::BytesMessage* pBytesMessage) :
    ACommand::_Dependencies(pCommand, pBytesMessage)
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

// Method(s)
void SecurityCommand::Execute()
{
    using namespace usx::geofactions;
    
    assert(m_pBytesMessage);

    std::string     strBrokerURI = "tcp://127.0.0.1:61613?wireFormat=stomp&keepAlive=true";
    std::string     strUUID = "";
    const SecurityCommandBuffer& aSecurityCommandBuffer = m_pCommand->securitycommandbuffer();
    
    if (SecurityCommandBuffer_SecurityCommandBufferType_JOIN == aSecurityCommandBuffer.type())
    {
        decaf::util::UUID aNewUUID = decaf::util::UUID::randomUUID();
        strUUID = aNewUUID.toString();
        const cms::Destination* pReplyToDestination = m_pBytesMessage->getCMSReplyTo();
        assert(pReplyToDestination);

        // TODO: Make not super inefficient
        SimpleAsyncProducer* pSimpleAsyncProducer = new SimpleAsyncProducer(strBrokerURI, pReplyToDestination, false, true);
        pSimpleAsyncProducer->Send(strUUID);
        delete pSimpleAsyncProducer;
        
        JoinedEvent(this, strUUID);
    }
    else if (SecurityCommandBuffer_SecurityCommandBufferType_LEAVE == aSecurityCommandBuffer.type())
    {
        assert(aSecurityCommandBuffer.has_uuid());
        strUUID = aSecurityCommandBuffer.uuid();
        
        LeftEvent(this, strUUID);
    }
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
