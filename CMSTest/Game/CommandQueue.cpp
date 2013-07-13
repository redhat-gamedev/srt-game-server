//
//  CommandQueue.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-13.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "CommandQueue.h"


// Constructor
CommandQueue::
_Dependencies::
_Dependencies(FactoryT<SecurityCommand, SecurityCommand::_Dependencies>& aSecurityCommandFactory, CommandConsumer& aCommandConsumer) :
    m_aSecurityCommandFactory(aSecurityCommandFactory),
    m_aCommandConsumer(aCommandConsumer)
{
    
}

// Destructor
CommandQueue::
_Dependencies::
~_Dependencies()
{
    
}


// Constructor
CommandQueue::CommandQueue(_Dependencies& theDependencies) :
    m_aSecurityCommandFactory(theDependencies.m_aSecurityCommandFactory),
    m_aCommandConsumer(theDependencies.m_aCommandConsumer)
{
    
}

// Destructor
CommandQueue::~CommandQueue()
{
    
}

// Method(s)
void CommandQueue::Execute()
{
    
}

// CommandConsumer Event response
void CommandQueue::HandleCommandConsumedEvent(const void* pSender, google::protobuf::Message*& pMessage)
{
    SecurityCommand::_Dependencies theSecurityCommandDependencies(*pMessage, );
    
    
    SecurityCommand* pSecurityCommand = m_aSecurityCommandFactory.Create(<#ACommand::_Dependencies &aD#>)
    
}