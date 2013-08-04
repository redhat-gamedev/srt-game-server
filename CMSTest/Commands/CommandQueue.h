//
//  CommandQueue.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-13.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__CommandQueue__
#define __CMSTest__CommandQueue__

#include "../Shared/FactoryT.h"
#include "SecurityCommand.h"
#include "JoinSecurityCommand.h"
#include "LeaveSecurityCommand.h"
#include "RawInputCommand.h"
#include "Poco/Tuple.h"
#include <decaf/util/StlQueue.h>

namespace google
{
    namespace protobuf
    {
        class Message;
    }
}
namespace cms
{
    class BytesMessage;
}
class CommandConsumer;


class CommandQueue
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        CommandConsumer&                                                                m_aCommandConsumer;
        FactoryT<JoinSecurityCommand, JoinSecurityCommand::_SecurityDependencies>&      m_aJoinSecurityCommandFactory;
        FactoryT<LeaveSecurityCommand, LeaveSecurityCommand::_SecurityDependencies>&    m_aLeaveSecurityCommandFactory;
        FactoryT<DualStickRawInputCommand, DualStickRawInputCommand::_RawInputDependencies>&    m_aDualStickRawInputCommandFactory;
        
        // Constructor
        _Dependencies(FactoryT<JoinSecurityCommand, JoinSecurityCommand::_SecurityDependencies>& aJoinSecurityCommandFactory,
                      FactoryT<LeaveSecurityCommand, LeaveSecurityCommand::_SecurityDependencies>& aLeaveSecurityCommandFactory,
                      FactoryT<DualStickRawInputCommand, DualStickRawInputCommand::_RawInputDependencies>&    aDualStickRawInputCommandFactory,
                      CommandConsumer& aCommandConsumer);
        
        // Destructor
        ~_Dependencies();
    };
private:
protected:
    CommandConsumer&                                                                m_aCommandConsumer;
    FactoryT<JoinSecurityCommand, JoinSecurityCommand::_SecurityDependencies>&      m_aJoinSecurityCommandFactory;
    FactoryT<LeaveSecurityCommand, LeaveSecurityCommand::_SecurityDependencies>&    m_aLeaveSecurityCommandFactory;
    FactoryT<DualStickRawInputCommand, DualStickRawInputCommand::_RawInputDependencies>&    m_aDualStickRawInputCommandFactory;
    decaf::util::StlQueue<ACommand*>                                                m_aCommandQueue;


    // Constructor
    CommandQueue(_Dependencies* pDependencies);
    
    // Destructor
    ~CommandQueue();

public:
    // Singleton
    static CommandQueue& Instance(_Dependencies* pDependencies = NULL)//unsigned int uiCapacity)
    {
        static CommandQueue  aCommandQueue(pDependencies);
        return aCommandQueue;
    }
    
    // Method(s)
    void Execute();
    
    // CommandConsumer Event response
    void HandleCommandConsumedEvent(const void* pSender, Poco::Tuple<cms::BytesMessage*, google::protobuf::Message*>*& pTuple);
    
};

#endif /* defined(__CMSTest__CommandQueue__) */
