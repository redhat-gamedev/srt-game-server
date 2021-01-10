#ifndef __SRT__CommandBufferFactory__
#define __SRT__CommandBufferFactory__

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
#include "../Proto/CommandBuffer.pb.h"
#include "../Proto/SecurityCommandBuffer.pb.h"
#include <string>
#include <assert.h>

using namespace redhatgamedev::srt;


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


class LeaveSecurityCommand_Dependencies :
    public SecurityCommand_Dependencies
{
private:
protected:
public:
    const std::string&           m_strUUID;
    
    // Constructor
    LeaveSecurityCommand_Dependencies(const SecurityCommandBuffer_SecurityCommandBufferType& anSecurityCommandBufferType,
                                      const std::string& strUUID);
    
    // Destructor
    ~LeaveSecurityCommand_Dependencies();
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
        
        redhatgamedev::srt::SecurityCommandBuffer* pSecurityCommand = pCommand->mutable_securitycommandbuffer();
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
        
        int                 iBodyBytes = 0;
        unsigned char*      pucBodyBytes = NULL;
        
        pucBodyBytes = pRawBytesPair->first;
        iBodyBytes = (int)(pRawBytesPair->second);
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        pCommand->ParseFromArray(pucBodyBytes, iBodyBytes);
        //assert(CommandBuffer_CommandBufferType_SECURITY == pCommand->type());
        //const SecurityCommandBuffer& aSecurityCommand = pCommand->securitycommandbuffer();
        //if (SecurityCommandBuffer_SecurityCommandBufferType_JOIN == aSecurityCommand.type())
        //{
        //    int i = 0;
        //    ++i;
        //}
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

template<>
class FactoryT<JoinSecurityCommandBuffer, SecurityCommand_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<JoinSecurityCommandBuffer, SecurityCommand_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<JoinSecurityCommandBuffer, SecurityCommand_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<JoinSecurityCommandBuffer, SecurityCommand_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<JoinSecurityCommandBuffer, SecurityCommand_Dependencies>  aCommandFactory;
        return aCommandFactory;
    }
    
    // Method(s)
    virtual CommandBuffer* Create(SecurityCommand_Dependencies& theSecurityCommand_Dependencies)
    {
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        pCommand->set_type(CommandBuffer_CommandBufferType_SECURITY);
        
        redhatgamedev::srt::SecurityCommandBuffer* pSecurityCommand = pCommand->mutable_securitycommandbuffer();
        assert(NULL != pSecurityCommand);
        //pSecurityCommand->set_type(theSecurityCommand_Dependencies.m_anSecurityCommandBufferType);
        pSecurityCommand->set_type(SecurityCommandBuffer_SecurityCommandBufferType_JOIN);
        
        redhatgamedev::srt::JoinSecurityCommandBuffer* pJoinSecurityCommand = pSecurityCommand->mutable_joinsecuritycommandbuffer();
        
        CreatedEvent(this, pCommand);
        return pCommand;
    }
    virtual CommandBuffer* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        int       iBodyBytes = 0;
        unsigned char*      pucBodyBytes = NULL;
        
        pucBodyBytes = pRawBytesPair->first;
        iBodyBytes = (int)(pRawBytesPair->second);
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        pCommand->ParseFromArray(pucBodyBytes, iBodyBytes);
        assert(CommandBuffer_CommandBufferType_SECURITY == pCommand->type());
        const SecurityCommandBuffer& aSecurityCommand = pCommand->securitycommandbuffer();
        if (SecurityCommandBuffer_SecurityCommandBufferType_JOIN == aSecurityCommand.type())
        {
            int i = 0;
            ++i;
        }
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

template<>
class FactoryT<LeaveSecurityCommandBuffer, LeaveSecurityCommand_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<LeaveSecurityCommandBuffer, LeaveSecurityCommand_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<LeaveSecurityCommandBuffer, LeaveSecurityCommand_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<LeaveSecurityCommandBuffer, LeaveSecurityCommand_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<LeaveSecurityCommandBuffer, LeaveSecurityCommand_Dependencies>  aCommandFactory;
        return aCommandFactory;
    }
    
    // Method(s)
    virtual CommandBuffer* Create(LeaveSecurityCommand_Dependencies& theLeaveSecurityCommand_Dependencies)
    {
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        pCommand->set_type(CommandBuffer_CommandBufferType_SECURITY);
        
        redhatgamedev::srt::SecurityCommandBuffer* pSecurityCommand = pCommand->mutable_securitycommandbuffer();
        assert(NULL != pSecurityCommand);
        //pSecurityCommand->set_type(theSecurityCommand_Dependencies.m_anSecurityCommandBufferType);
        pSecurityCommand->set_type(SecurityCommandBuffer_SecurityCommandBufferType_LEAVE);
        
        redhatgamedev::srt::LeaveSecurityCommandBuffer* pLeaveSecurityCommand = pSecurityCommand->mutable_leavesecuritycommandbuffer();
        
        // TODO: Player UUID -> Add UUID to the SecurityCommandDependencies and fix this 071413!
        //pLeaveSecurityCommand->set_uuid("test");
        pLeaveSecurityCommand->set_uuid(theLeaveSecurityCommand_Dependencies.m_strUUID);
        
        CreatedEvent(this, pCommand);
        return pCommand;
    }
    virtual CommandBuffer* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        CommandBuffer aCommand;
        CommandBuffer* pCommand = aCommand.New();
        
        int       iBodyBytes = 0;
        unsigned char*      pucBodyBytes = NULL;
        
        pucBodyBytes = pRawBytesPair->first;
        iBodyBytes = (int)(pRawBytesPair->second);
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        pCommand->ParseFromArray(pucBodyBytes, iBodyBytes);
        assert(CommandBuffer_CommandBufferType_SECURITY == pCommand->type());
        const SecurityCommandBuffer& aSecurityCommand = pCommand->securitycommandbuffer();
        if (SecurityCommandBuffer_SecurityCommandBufferType_LEAVE == aSecurityCommand.type())
        {
            int i = 0;
            ++i;
        }
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

#endif /* defined(__SRT__CommandBufferFactory__) */
