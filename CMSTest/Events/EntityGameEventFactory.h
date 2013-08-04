//
//  GameEventFactory.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-07-07.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__GameEventFactory__
#define __CMSTest__GameEventFactory__

#include "../Shared/FactoryT.h"
#include "../proto/GameEventBuffer.pb.h"
#include "../proto/EntityGameEventBuffer.pb.h"
#include "../Game/AEntity.h"
#include <assert.h>

using namespace usx::geofactions;

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
    FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>& Instance()//unsigned int uiCapacity)
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

class EntityGameEventFactory :
    public FactoryT<GameEventBuffer, EntityGameEvent_Dependencies>
{
private:
protected:
//    // Constructor(s)
//    EntityGameEventFactory() {};
//    
//    // Destructor(s)
//    ~EntityGameEventFactory() {};
//    
//public:
//    // Singleton
//    static EntityGameEventFactory& Instance()
//    {
//        static EntityGameEventFactory  anEntityGameEventFactory;
//        return anEntityGameEventFactory;
//    }
//    
//    virtual EntityGameEvent* Create(EntityGameEvent_Dependencies& anEntityGameEvent_Dependencies);
};

#endif /* defined(__CMSTest__GameEventFactory__) */
