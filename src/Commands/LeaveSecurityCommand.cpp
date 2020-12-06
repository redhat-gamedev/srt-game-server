//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

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
    using namespace redhatgamedev::srt;
    
    assert(m_pCommandBuffer);
    
    const SecurityCommandBuffer& aSecurityCommandBuffer = m_pCommandBuffer->securitycommandbuffer();
    const LeaveSecurityCommandBuffer& aLeaveSecurityCommandBuffer = aSecurityCommandBuffer.leavesecuritycommandbuffer();
    const std::string& strUUID = aLeaveSecurityCommandBuffer.uuid();
    
    ExecutedEvent(this, strUUID);
}
