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

#include "ACommand.h"
#include <assert.h>


// Constructor
ACommand::
_Dependencies::
_Dependencies(redhatgamedev::srt::CommandBuffer* pCommandBuffer, const proton::message* pBytesMessage) :
    m_pCommandBuffer(pCommandBuffer),
    m_pBytesMessage(pBytesMessage)
{
    assert(m_pCommandBuffer);
    assert(m_pBytesMessage);
    
}

// Destructor
ACommand::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
ACommand::ACommand(_Dependencies& theDependencies) :
    m_pCommandBuffer(theDependencies.m_pCommandBuffer),
    m_pBytesMessage(theDependencies.m_pBytesMessage)
{
    assert(m_pCommandBuffer);
    assert(m_pBytesMessage);
}

// Destructor
ACommand::~ACommand()
{
    
}
