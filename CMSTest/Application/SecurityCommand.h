//
//  SecurityCommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__SecurityCommand__
#define __CMSTest__SecurityCommand__

#include "../Shared/ACommand.h"

namespace command
{
    class Command;
    class SecurityCommand;
}
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


class SecurityCommand :
    public ACommand
{
public:
    class _SecurityDependencies :
        public _Dependencies
    {
    private:
    protected:
    public:
        // Constructor
        _SecurityDependencies(command::Command* pCommand, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        ~_SecurityDependencies();
    };
    
private:
protected:
public:
    // Constructor
    SecurityCommand(_SecurityDependencies& theDependencies);
    
    // Destructor
    ~SecurityCommand();
    
    // Method(s)
    virtual void Execute();
};


//class JoinSecurityCommand :
//    public SecurityCommand
//{
//private:
//protected:
//public:
//    // Constructor
//    JoinSecurityCommand(_Dependencies& theDependencies);
//    
//    // Destructor
//    ~JoinSecurityCommand();
//    
//    // Method(s)
//    virtual void Execute();
//};



#endif /* defined(__CMSTest__SecurityCommand__) */
