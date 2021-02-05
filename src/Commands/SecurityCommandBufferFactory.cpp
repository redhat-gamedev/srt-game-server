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

#include "SecurityCommandBufferFactory.h"


// Constructor
SecurityCommand_Dependencies::
SecurityCommand_Dependencies(const SecurityCommandBuffer_SecurityCommandBufferType& anSecurityCommandBufferType) :
    m_anSecurityCommandBufferType(anSecurityCommandBufferType)
{
}

// Destructor
SecurityCommand_Dependencies::
~SecurityCommand_Dependencies()
{
    
}


// Constructor
LeaveSecurityCommand_Dependencies::
LeaveSecurityCommand_Dependencies(const SecurityCommandBuffer_SecurityCommandBufferType& anSecurityCommandBufferType,
                                  const std::string& strUUID) :
    m_strUUID(strUUID),
    SecurityCommand_Dependencies(anSecurityCommandBufferType)
{
}

// Destructor
LeaveSecurityCommand_Dependencies::
~LeaveSecurityCommand_Dependencies()
{
    
}
