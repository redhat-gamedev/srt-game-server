//
//  ACommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Command__
#define __CMSTest__Command__

namespace command
{
    class Command;
}


class ICommand
{
public:
    virtual void Execute() = 0;
};


class ACommand :
    public ICommand
{
public:
    class _Dependencies
    {
    private:
    protected:
    public:
        command::Command&       m_aCommand;
        
        // Constructor
        _Dependencies(command::Command& aCommand);
        
        // Destructor
        virtual ~_Dependencies();
    };
    
protected:
    command::Command&       m_aCommand;
    
    // Constructor
    ACommand(_Dependencies& theDependencies);
    
    // Destructor
    virtual ~ACommand();
    
public:
    // Method(s)
    virtual void Execute() = 0;
};

#endif /* defined(__CMSTest__Command__) */
