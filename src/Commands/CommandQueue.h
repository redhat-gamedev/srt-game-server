#ifndef __SRT__CommandQueue__
#define __SRT__CommandQueue__

//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "../Shared/FactoryT.h"
#include "SecurityCommand.h"
#include "JoinSecurityCommand.h"
#include "LeaveSecurityCommand.h"
#include "RawInputCommand.h"
#include "DualStickRawInputCommand.h"
#include <Poco/Tuple.h>
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

#endif /* defined(__SRT__CommandQueue__) */
