//
//  SecurityCommandBufferFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-14.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__CommandBufferFactory__
#define __CMSTest__CommandBufferFactory__

#include "../Shared/FactoryT.h"
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include <assert.h>

using namespace CommandBuffers;


class SecurityCommand_Dependencies
{
private:
protected:
public:
    const SecurityCommandBuffer_SecurityCommandBufferType&      m_anSecurityCommandBufferType;
    
    // Constructor
    SecurityCommand_Dependencies(const SecurityCommandBuffer_SecurityCommandBufferType& anSecurityCommandBufferType);
    
    // Destructor
    ~SecurityCommand_Dependencies();
};

//template<class T, class D>
//class FactoryT<T*, D*> :
//    public FactoryT<SecurityCommand*, SecurityCommand_Dependencies>
//
//template<>
//class FactoryT<SecurityCommand*, SecurityCommand_Dependencies>
//

template<>
class FactoryT<CommandBuffer, SecurityCommand_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<CommandBuffer, SecurityCommand_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<CommandBuffer, SecurityCommand_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<CommandBuffer, SecurityCommand_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<CommandBuffer, SecurityCommand_Dependencies>  aCommandFactory;
        return aCommandFactory;
    }
    
    // Method(s)
    virtual CommandBuffer* Create(SecurityCommand_Dependencies& theSecurityCommand_Dependencies)
    {
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        pCommand->set_type(CommandBuffer_CommandBufferType_SECURITY);
        
        CommandBuffers::SecurityCommandBuffer* pSecurityCommand = pCommand->mutable_securitycommandbuffer();
        assert(NULL != pSecurityCommand);
        pSecurityCommand->set_type(theSecurityCommand_Dependencies.m_anSecurityCommandBufferType);
        
        CreatedEvent(this, pCommand);
        return pCommand;
    }
    virtual CommandBuffer* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        unsigned long       iBodyBytes = 0;
        unsigned char*      pucBodyBytes = NULL;
        
        pucBodyBytes = pRawBytesPair->first;
        iBodyBytes = pRawBytesPair->second;
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        pCommand->ParseFromArray(pucBodyBytes, iBodyBytes);
        
        delete[] pucBodyBytes;
        pucBodyBytes = NULL;
        delete pRawBytesPair;
        
        return pCommand;
    }
    virtual void Destroy(CommandBuffer*& pCommand)
    {
        DestroyedEvent(this, pCommand);
        delete pCommand;
        pCommand = NULL;
    }
    
    // Event(s)
    Poco::BasicEvent<CommandBuffer*&>    CreatedEvent;
    Poco::BasicEvent<CommandBuffer*&>    DestroyedEvent;
};

class SecurityCommandFactory :
    public FactoryT<CommandBuffer, SecurityCommand_Dependencies>
{
private:
protected:
    //    // Constructor(s)
    //    SecurityCommandFactory() {};
    //
    //    // Destructor(s)
    //    ~SecurityCommandFactory() {};
    //
    //public:
    //    // Singleton
    //    static SecurityCommandFactory& Instance()
    //    {
    //        static SecurityCommandFactory  anSecurityCommandFactory;
    //        return anSecurityCommandFactory;
    //    }
    //
    //    virtual SecurityCommand* Create(SecurityCommand_Dependencies& anSecurityCommand_Dependencies);
};

#endif /* defined(__CMSTest__CommandBufferFactory__) */
