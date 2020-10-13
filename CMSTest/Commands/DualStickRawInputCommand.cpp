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

#include "DualStickRawInputCommand.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/RawInputCommandBuffer.pb.h"
#include <assert.h>


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
