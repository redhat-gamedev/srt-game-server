//
//  LeaveSecurityCommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "LeaveSecurityCommand.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include <assert.h>


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