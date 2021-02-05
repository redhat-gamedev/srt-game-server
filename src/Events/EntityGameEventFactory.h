#ifndef __SRT__GameEventFactory__
#define __SRT__GameEventFactory__

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
#include "../Proto/EntityGameEventBuffer.pb.h"
#include "../Game/AEntity.h"
#include <assert.h>

using namespace redhatgamedev::srt;

class AEntity;


class EntityGameEvent_Dependencies
{
private:
protected:
public:
    const EntityGameEventBuffer_EntityGameEventBufferType&      m_anEntityGameEventBufferType;
    AEntity*&                                       m_pEntity;
    
    // Constructor
    EntityGameEvent_Dependencies(const EntityGameEventBuffer_EntityGameEventBufferType& anEntityGameEventBufferType, AEntity*& pEntity);
    
    // Destructor
    ~EntityGameEvent_Dependencies();
};

template<>
class FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>() {};
    
    // Destructor(s)
    virtual ~FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>& Instance()
    {
        static FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>  aGameEventFactory;
        return aGameEventFactory;
    }
    
    // Method(s)
    virtual GameEventBuffer* Create(EntityGameEvent_Dependencies& theEntityGameEvent_Dependencies)
    {
        GameEventBuffer aGameEvent;
        GameEventBuffer* pGameEvent = aGameEvent.New();
        
        pGameEvent->set_type(GameEventBuffer_GameEventBufferType_ENTITY);
        
        EntityGameEventBuffer* pEntityGameEvent = pGameEvent->mutable_entitygameeventbuffer();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(theEntityGameEvent_Dependencies.m_anEntityGameEventBufferType);
        AEntity::Serializer.Serialize(theEntityGameEvent_Dependencies.m_pEntity, pEntityGameEvent);
        
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


#endif /* defined(__SRT__GameEventFactory__) */
