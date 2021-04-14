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
#include "../Application/Configuration.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include <proton/message.hpp>
#include <assert.h>
#include "../Logging/loguru.hpp"


// Constructor
LeaveSecurityCommand::LeaveSecurityCommand(_SecurityDependencies& theDependencies) :
    SecurityCommand(theDependencies)
{

}

// Destructor
LeaveSecurityCommand::~LeaveSecurityCommand()
{
    
}

// Method(s)
void LeaveSecurityCommand::Execute()
{
    using namespace redhatgamedev::srt;
    
    assert(m_pBytesMessage);
    assert(m_pCommandBuffer);
    
    std::string     strUUID = "";
    const SecurityCommandBuffer& aSecurityCommandBuffer = m_pCommandBuffer->securitycommandbuffer();
    LOG_SCOPE_F(INFO, "provided player identity: %s", aSecurityCommandBuffer.uuid().c_str());

    //const LeaveSecurityCommandBuffer& aLeaveSecurityCommandBuffer = aSecurityCommandBuffer.leavesecuritycommandbuffer();
    strUUID = aSecurityCommandBuffer.uuid();
    
    ExecutedEvent(this, strUUID);
}
