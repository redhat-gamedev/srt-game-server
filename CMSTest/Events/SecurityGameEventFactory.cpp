//
//  SecurityGameEventFactory.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

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
