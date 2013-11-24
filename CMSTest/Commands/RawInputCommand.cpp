//
//  RawInputCommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "RawInputCommand.h"
#include "../Proto/CommandBuffer.pb.h"
#include <cms/BytesMessage.h>
#include <assert.h>


// Constructor
RawInputCommand::
_RawInputDependencies::
_RawInputDependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage) :
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
