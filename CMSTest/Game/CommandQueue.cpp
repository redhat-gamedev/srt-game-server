//
//  CommandQueue.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-13.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "CommandQueue.h"
#include "CommandConsumer.h"
#include "ACommand.h"
#include "../Proto/Command.pb.h"
#include "Poco/Delegate.h"



// Constructor
CommandQueue::
_Dependencies::
_Dependencies(FactoryT<SecurityCommand, SecurityCommand::_SecurityDependencies>& aSecurityCommandFactory, CommandConsumer& aCommandConsumer) :
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
CommandQueue::CommandQueue(_Dependencies* pDependencies) :
    m_aSecurityCommandFactory(pDependencies->m_aSecurityCommandFactory),
    m_aCommandConsumer(pDependencies->m_aCommandConsumer)
{
    using namespace Poco;
    using namespace cms;
    
    m_aCommandConsumer.CommandConsumedEvent += Delegate<CommandQueue, Tuple<BytesMessage*, google::protobuf::Message*>*& >(this, &CommandQueue::HandleCommandConsumedEvent);
}

// Destructor
CommandQueue::~CommandQueue()
{
    using namespace Poco;
    using namespace cms;
    
    m_aCommandConsumer.CommandConsumedEvent -= Delegate<CommandQueue, Tuple<BytesMessage*, google::protobuf::Message*>*& >(this, &CommandQueue::HandleCommandConsumedEvent);
}

// Method(s)
void CommandQueue::Execute()
{
    ACommand* pCommand = NULL;
    m_aCommandQueue.lock();
    while (!m_aCommandQueue.empty())
    {
        pCommand = m_aCommandQueue.pop();
        pCommand->Execute();
    }
    m_aCommandQueue.unlock();
}

// CommandConsumer Event response
void CommandQueue::HandleCommandConsumedEvent(const void* pSender, Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>*& pTuple)
{
    command::Command* pCommand = dynamic_cast<command::Command*>(pTuple->get<1>());
    cms::BytesMessage* pBytesMessage = pTuple->get<0>();
    
    SecurityCommand::_SecurityDependencies theSecurityCommandDependencies(pCommand, pBytesMessage);
    SecurityCommand* pSecurityCommand = m_aSecurityCommandFactory.Create(theSecurityCommandDependencies);
    
    m_aCommandQueue.lock();
    m_aCommandQueue.push(pSecurityCommand);
    m_aCommandQueue.unlock();
}