//
//  SecurityCommandBufferFactory.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-14.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "SecurityCommandBufferFactory.h"
#include <assert.h>


// Constructor
SecurityCommand_Dependencies::
SecurityCommand_Dependencies(const SecurityCommand_SecurityCommandType& anSecurityCommandType) :
    m_anSecurityCommandType(anSecurityCommandType)
{
}

// Destructor
SecurityCommand_Dependencies::
~SecurityCommand_Dependencies()
{
    
}


//SecurityCommand* SecurityCommandFactory::Create(SecurityCommand_Dependencies& anSecurityCommand_Dependencies)
//{
//    SecurityCommand* pSecurityCommand = NULL;
//
//    CreatedEvent(this, pSecurityCommand);
//    return pSecurityCommand;
//}
