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

#include "SecurityGameEventFactory.h"
#include <assert.h>


// Constructor
SecurityGameEvent_Dependencies::
SecurityGameEvent_Dependencies(const SecurityGameEventBuffer_SecurityGameEventBufferType& anSecurityGameEventBufferType, const std::string& strUUID) :
    m_anSecurityGameEventBufferType(anSecurityGameEventBufferType),
    m_strUUID(strUUID)
{
    assert(m_strUUID.length() > 0);
}

// Destructor
SecurityGameEvent_Dependencies::
~SecurityGameEvent_Dependencies()
{
    
}


//SecurityGameEvent* SecurityGameEventFactory::Create(SecurityGameEvent_Dependencies& anSecurityGameEvent_Dependencies)
//{
//    SecurityGameEvent* pSecurityGameEvent = NULL;
//
//    CreatedEvent(this, pSecurityGameEvent);
//    return pSecurityGameEvent;
//}
