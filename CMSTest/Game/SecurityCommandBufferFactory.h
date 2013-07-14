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
#include "../Proto/Command.pb.h"
#include "../Proto/SecurityCommand.pb.h"
#include <assert.h>

using namespace command;


class SecurityCommand_Dependencies
{
private:
protected:
public:
    const SecurityCommand_SecurityCommandType&      m_anSecurityCommandType;
    
    // Constructor
    SecurityCommand_Dependencies(const SecurityCommand_SecurityCommandType& anSecurityCommandType);
    
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
class FactoryT<Command, SecurityCommand_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<Command, SecurityCommand_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<Command, SecurityCommand_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<Command, SecurityCommand_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<Command, SecurityCommand_Dependencies>  aCommandFactory;
        return aCommandFactory;
    }
    
    // Method(s)
    virtual Command* Create(SecurityCommand_Dependencies& theSecurityCommand_Dependencies)
    {
        Command aCommand;
        Command* pCommand = aCommand.New();
        
        pCommand->set_type(Command_CommandType_SECURITY);
        
        command::SecurityCommand* pSecurityCommand = pCommand->mutable_securitycommand();
        assert(NULL != pSecurityCommand);
        pSecurityCommand->set_type(theSecurityCommand_Dependencies.m_anSecurityCommandType);
        
        CreatedEvent(this, pCommand);
        return pCommand;
    }
    virtual Command* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        Command aCommand;
        Command* pCommand = aCommand.New();
        
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
    virtual void Destroy(Command*& pCommand)
    {
        DestroyedEvent(this, pCommand);
        delete pCommand;
        pCommand = NULL;
    }
    
    // Event(s)
    Poco::BasicEvent<Command*&>    CreatedEvent;
    Poco::BasicEvent<Command*&>    DestroyedEvent;
};

class SecurityCommandFactory :
    public FactoryT<Command, SecurityCommand_Dependencies>
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
