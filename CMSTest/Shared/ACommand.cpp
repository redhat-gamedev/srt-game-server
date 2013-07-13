//
//  ACommand.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "ACommand.h"


// Constructor
ACommand::
_Dependencies::
_Dependencies(command::Command& aCommand) :
    m_aCommand(aCommand)
{
    
}

// Destructor
ACommand::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
ACommand::ACommand(_Dependencies& theDependencies) :
    m_aCommand(theDependencies.m_aCommand)
{
    
}

// Destructor
ACommand::~ACommand()
{
    
}