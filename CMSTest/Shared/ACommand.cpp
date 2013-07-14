//
//  ACommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "ACommand.h"
#include <assert.h>


// Constructor
ACommand::
_Dependencies::
_Dependencies(usx::geofactions::CommandBuffer* pCommand, const cms::BytesMessage* pBytesMessage) :
    m_pCommand(pCommand),
    m_pBytesMessage(pBytesMessage)
{
    assert(m_pCommand);
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
    m_pCommand(theDependencies.m_pCommand),
    m_pBytesMessage(theDependencies.m_pBytesMessage)
{
    assert(m_pCommand);
    assert(m_pBytesMessage);
}

// Destructor
ACommand::~ACommand()
{
    
}