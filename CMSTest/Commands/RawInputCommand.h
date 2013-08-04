//
//  RawInputCommand.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-08-04.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__RawInputCommand__
#define __CMSTest__RawInputCommand__

#include "../Shared/ACommand.h"
#include "Poco/BasicEvent.h"

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


class RawInputCommand :
    public ACommand
{
public:
    class _RawInputDependencies :
        public _Dependencies
    {
    private:
    protected:
    public:
        // Constructor
        _RawInputDependencies(usx::geofactions::CommandBuffer* pCommandBuffer, const cms::BytesMessage* pBytesMessage);
        
        // Destructor
        ~_RawInputDependencies();
    };
    
private:
protected:
public:
    // Constructor
    RawInputCommand(_RawInputDependencies& theDependencies);
    
    // Destructor
    virtual ~RawInputCommand();
    
    // Method(s)
    virtual void Execute() = 0;
};


class DualStickRawInputCommand :
    public RawInputCommand
{
private:
protected:
public:
    // Event(s)
    Poco::BasicEvent<const std::string&>      ExecutedEvent;
    
    // Constructor
    DualStickRawInputCommand(_RawInputDependencies& theDependencies);
    
    // Destructor
    ~DualStickRawInputCommand();
    
    // Method(s)
    virtual void Execute();
};
#endif /* defined(__CMSTest__RawInputCommand__) */
