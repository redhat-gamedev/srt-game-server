#ifndef __SRT__SecurityGameEventFactory__
#define __SRT__SecurityGameEventFactory__

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
#include "../Proto/GameEventBuffer.pb.h"
#include <string>
#include <assert.h>

using namespace redhatgamedev::srt;


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
    FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>() {};
    
    // Destructor(s)
    virtual ~FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<GameEventBuffer, SecurityGameEvent_Dependencies>& Instance()
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


#endif /* defined(__SRT__SecurityGameEventFactory__) */
