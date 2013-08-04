//
//  JoinSecurityCommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__JoinSecurityCommand__
#define __CMSTest__JoinSecurityCommand__

#include "SecurityCommand.h"
#include <string>


class JoinSecurityCommand :
    public SecurityCommand
{
private:
protected:
public:
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    
    // Constructor
    JoinSecurityCommand(_SecurityDependencies& theDependencies);
    
    // Destructor
    ~JoinSecurityCommand();
    
    // Method(s)
    virtual void Execute();
};


#endif /* defined(__CMSTest__JoinSecurityCommand__) */
