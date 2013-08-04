//
//  LeaveSecurityCommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__LeaveSecurityCommand__
#define __CMSTest__LeaveSecurityCommand__

#include "SecurityCommand.h"
#include <string>


class LeaveSecurityCommand :
    public SecurityCommand
{
private:
protected:
public:
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    
    // Constructor
    LeaveSecurityCommand(_SecurityDependencies& theDependencies);
    
    // Destructor
    ~LeaveSecurityCommand();
    
    // Method(s)
    virtual void Execute();
};


#endif /* defined(__CMSTest__LeaveSecurityCommand__) */
