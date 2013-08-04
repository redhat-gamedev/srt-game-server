//
//  SecurityGameEventFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__SecurityGameEventFactory__
#define __CMSTest__SecurityGameEventFactory__

#include "../Shared/FactoryT.h"
#include "../proto/GameEventBuffer.pb.h"
//#include "../proto/SecurityGameEventBuffer.pb.h"
#include <string>
#include <assert.h>

using namespace usx::geofactions;

//class ASecurity;


class SecurityGameEvent_Dependencies
{
private:
protected:
public:
    const SecurityGameEventBuffer_SecurityGameEventBufferType&      m_anSecurityGameEventBufferType;
    const std::string&                                              m_strUUID;
    
    // Constructor
    SecurityGameEvent_Dependencies(const SecurityGameEventBuffer_SecurityGameEventBufferType& anSecurityGameEventBufferType, const std::string& strUUID);
    
    // Destructor
    ~SecurityGameEvent_Dependencies();
};

template<>
class FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>  aGameEventFactory;
        return aGameEventFactory;
    }
    
    // Method(s)
    virtual GameEventBuffer* Create(SecurityGameEvent_Dependencies& theSecurityGameEvent_Dependencies)
    {
        GameEventBuffer aGameEvent;
        GameEventBuffer* pGameEvent = aGameEvent.New();
        
        pGameEvent->set_type(GameEventBuffer_GameEventBufferType_SECURITY);
        
        SecurityGameEventBuffer* pSecurityGameEvent = pGameEvent->mutable_securitygameeventbuffer();
        assert(NULL != pSecurityGameEvent);
        pSecurityGameEvent->set_type(theSecurityGameEvent_Dependencies.m_anSecurityGameEventBufferType);
        if (SecurityGameEventBuffer_SecurityGameEventBufferType_JOIN == theSecurityGameEvent_Dependencies.m_anSecurityGameEventBufferType)
        {
            JoinSecurityGameEventBuffer* pJoinSecurityGameEventBuffer = pSecurityGameEvent->mutable_joinsecuritygameeventbuffer();
            pJoinSecurityGameEventBuffer->set_uuid(theSecurityGameEvent_Dependencies.m_strUUID);
        }
        else if (SecurityGameEventBuffer_SecurityGameEventBufferType_LEAVE == theSecurityGameEvent_Dependencies.m_anSecurityGameEventBufferType)
        {
            LeaveSecurityGameEventBuffer* pLeaveSecurityGameEventBuffer = pSecurityGameEvent->mutable_leavesecuritygameeventbuffer();
            pLeaveSecurityGameEventBuffer->set_uuid(theSecurityGameEvent_Dependencies.m_strUUID);
        }
        
        CreatedEvent(this, pGameEvent);
        return pGameEvent;
    }
    virtual GameEventBuffer* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        GameEventBuffer aGameEvent;
        GameEventBuffer* pGameEvent = aGameEvent.New();
        
        unsigned long       iBodyBytes = 0;
        unsigned char*      pucBodyBytes = NULL;
        
        pucBodyBytes = pRawBytesPair->first;
        iBodyBytes = pRawBytesPair->second;
        assert(pucBodyBytes);
        assert(iBodyBytes > 0);
        
        pGameEvent->ParseFromArray(pucBodyBytes, iBodyBytes);
        
        delete[] pucBodyBytes;
        pucBodyBytes = NULL;
        delete pRawBytesPair;
        
        return pGameEvent;
    }
    virtual void Destroy(GameEventBuffer*& pGameEvent)
    {
        DestroyedEvent(this, pGameEvent);
        delete pGameEvent;
        pGameEvent = NULL;
    }
    
    // Event(s)
    Poco::BasicEvent<GameEventBuffer*&>    CreatedEvent;
    Poco::BasicEvent<GameEventBuffer*&>    DestroyedEvent;
};

class SecurityGameEventFactory :
    public FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>
{
private:
protected:
    //    // Constructor(s)
    //    SecurityGameEventFactory() {};
    //
    //    // Destructor(s)
    //    ~SecurityGameEventFactory() {};
    //
    //public:
    //    // Singleton
    //    static SecurityGameEventFactory& Instance()
    //    {
    //        static SecurityGameEventFactory  anSecurityGameEventFactory;
    //        return anSecurityGameEventFactory;
    //    }
    //
    //    virtual SecurityGameEvent* Create(SecurityGameEvent_Dependencies& anSecurityGameEvent_Dependencies);
};

#endif /* defined(__CMSTest__SecurityGameEventFactory__) */
