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

#include "RawInputCommand.h"
#include "../Proto/CommandBuffer.pb.h"
//#include <cms/BytesMessage.h>
#include <assert.h>


// Constructor
RawInputCommand::
_RawInputDependencies::
_RawInputDependencies(redhatgamedev::srt::CommandBuffer* pCommandBuffer, const proton::message* pBytesMessage) :
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
