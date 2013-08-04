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
_Dependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage) :
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