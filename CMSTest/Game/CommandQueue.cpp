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
#include "../Proto/CommandBuffer.pb.h"
#include "Poco/Delegate.h"



// Constructor
CommandQueue::
_Dependencies::
_Dependencies(FactoryT<JoinSecurityCommand, JoinSecurityCommand::_SecurityDependencies>& aJoinSecurityCommandFactory,
              FactoryT<LeaveSecurityCommand, LeaveSecurityCommand::_SecurityDependencies>& aLeaveSecurityCommandFactory,
              FactoryT<DualStickRawInputCommand, DualStickRawInputCommand::_RawInputDependencies>&    aDualStickRawInputCommandFactory,
              CommandConsumer& aCommandConsumer) :
    m_aJoinSecurityCommandFactory(aJoinSecurityCommandFactory),
    m_aLeaveSecurityCommandFactory(aLeaveSecurityCommandFactory),
    m_aDualStickRawInputCommandFactory(aDualStickRawInputCommandFactory),
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
    m_aJoinSecurityCommandFactory(pDependencies->m_aJoinSecurityCommandFactory),
    m_aLeaveSecurityCommandFactory(pDependencies->m_aLeaveSecurityCommandFactory),
    m_aDualStickRawInputCommandFactory(pDependencies->m_aDualStickRawInputCommandFactory),
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
    usx::geofactions::CommandBuffer* pCommandBuffer = dynamic_cast<usx::geofactions::CommandBuffer*>(pTuple->get<1>());
    cms::BytesMessage* pBytesMessage = pTuple->get<0>();
    
    ACommand* pCommand = NULL;

    if (usx::geofactions::CommandBuffer_CommandBufferType_SECURITY == pCommandBuffer->type())
    {
        const SecurityCommandBuffer& aSecurityCommandBuffer = pCommandBuffer->securitycommandbuffer();
        if (usx::geofactions::SecurityCommandBuffer_SecurityCommandBufferType_JOIN == aSecurityCommandBuffer.type())
        {
            JoinSecurityCommand::_SecurityDependencies theJoinSecurityCommandDependencies(pCommandBuffer, pBytesMessage);
            pCommand = m_aJoinSecurityCommandFactory.Create(theJoinSecurityCommandDependencies);
        }
        else if (usx::geofactions::SecurityCommandBuffer_SecurityCommandBufferType_LEAVE == aSecurityCommandBuffer.type())
        {
            LeaveSecurityCommand::_SecurityDependencies theLeaveSecurityCommandDependencies(pCommandBuffer, pBytesMessage);
            pCommand = m_aLeaveSecurityCommandFactory.Create(theLeaveSecurityCommandDependencies);
        }
        else //usx::geofactions::SecurityCommandBuffer_SecurityCommandBufferType_UNKNOWN
        {
            assert(false);
        }
    }
    else if (usx::geofactions::CommandBuffer_CommandBufferType_RAWINPUT == pCommandBuffer->type())
    {
        const RawInputCommandBuffer& aRawInputCommandBuffer = pCommandBuffer->rawinputcommandbuffer();
        if (usx::geofactions::RawInputCommandBuffer_RawInputCommandBufferType_DUALSTICK == aRawInputCommandBuffer.type())
        {
            DualStickRawInputCommand::_RawInputDependencies theDualStickRawInputCommandDependencies(pCommandBuffer, pBytesMessage);
            pCommand = m_aDualStickRawInputCommandFactory.Create(theDualStickRawInputCommandDependencies);
        }
        else //usx::geofactions::SecurityCommandBuffer_SecurityCommandBufferType_UNKNOWN
        {
            assert(false);
        }
    }
    else //usx::geofactions::CommandBuffer_CommandBufferType_UNKNOWN:
    {
        assert(false);
    }
    
    assert(pCommand);
    m_aCommandQueue.lock();
    m_aCommandQueue.push(pCommand);
    m_aCommandQueue.unlock();
}
