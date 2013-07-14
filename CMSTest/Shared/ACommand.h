//
//  ACommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-11.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Command__
#define __CMSTest__Command__

namespace CommandBuffers
{
    class CommandBuffer;
}
namespace cms
{
    class BytesMessage;
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
        const cms::BytesMessage*        m_pBytesMessage;
        CommandBuffers::CommandBuffer*               m_pCommand;
        
        // Constructor
        _Dependencies(CommandBuffers::CommandBuffer* pCommand, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        virtual ~_Dependencies();
    };
    
protected:
    const cms::BytesMessage*        m_pBytesMessage;
    CommandBuffers::CommandBuffer*               m_pCommand;
    
    // Constructor
    ACommand(_Dependencies& theDependencies);
    
    // Destructor
    virtual ~ACommand();
    
public:
    // Method(s)
    virtual void Execute() = 0;
};

#endif /* defined(__CMSTest__Command__) */
