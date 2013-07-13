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

namespace google
{
    namespace protobuf
    {
        class Message;
    }
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
        CommandConsumer&                                                m_aCommandConsumer;
        FactoryT<SecurityCommand, SecurityCommand::_Dependencies>&      m_aSecurityCommandFactory;
        
        // Constructor
        _Dependencies(FactoryT<SecurityCommand, SecurityCommand::_Dependencies>& aSecurityCommandFactory, CommandConsumer& aCommandConsumer);
        
        // Destructor
        ~_Dependencies();
    };
private:
protected:
    CommandConsumer&                                                m_aCommandConsumer;
    FactoryT<SecurityCommand, SecurityCommand::_Dependencies>&      m_aSecurityCommandFactory;
    
public:
    // Constructor
    CommandQueue(_Dependencies& theDependencies);
    
    // Destructor
    ~CommandQueue();

    // Method(s)
    void Execute();
    
    // CommandConsumer Event response
    void HandleCommandConsumedEvent(const void* pSender, google::protobuf::Message*& pMessage);
    
};

#endif /* defined(__CMSTest__CommandQueue__) */
