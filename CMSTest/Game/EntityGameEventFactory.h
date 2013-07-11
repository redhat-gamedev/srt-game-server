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
#include "../proto/GameEvent.pb.h"
#include "../proto/EntityGameEvent.pb.h"
#include "AEntity.h"
#include <assert.h>

using namespace gameevent;

class AEntity;


class EntityGameEvent_Dependencies
{
private:
protected:
public:
    const EntityGameEvent_EntityGameEventType&      m_anEntityGameEventType;
    AEntity*&                                       m_pEntity;
    
    // Constructor
    EntityGameEvent_Dependencies(const EntityGameEvent_EntityGameEventType& anEntityGameEventType, AEntity*& pEntity);
    
    // Destructor
    ~EntityGameEvent_Dependencies();
};

//template<class T, class D>
//class FactoryT<T*, D*> :
//    public FactoryT<EntityGameEvent*, EntityGameEvent_Dependencies>
//
//template<>
//class FactoryT<EntityGameEvent*, EntityGameEvent_Dependencies>
//

template<>
class FactoryT<GameEvent, EntityGameEvent_Dependencies>
{
private:
    
protected:
    // Constructor(s)
    FactoryT<GameEvent, EntityGameEvent_Dependencies>() {};//unsigned int uiCapacity, unsigned int uiPeakCapacity) {};
    
    // Destructor(s)
    virtual ~FactoryT<GameEvent, EntityGameEvent_Dependencies>() {};
    
public:
    // Singleton
    static FactoryT<GameEvent, EntityGameEvent_Dependencies>& Instance()//unsigned int uiCapacity)
    {
        static FactoryT<GameEvent, EntityGameEvent_Dependencies>  aGameEventFactory;
        return aGameEventFactory;
    }
    
    // Method(s)
    virtual GameEvent* Create(EntityGameEvent_Dependencies& theEntityGameEvent_Dependencies)
    {
        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        
        pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
        
        EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
        assert(NULL != pEntityGameEvent);
        pEntityGameEvent->set_type(theEntityGameEvent_Dependencies.m_anEntityGameEventType);
        AEntity::Serializer.Serialize(theEntityGameEvent_Dependencies.m_pEntity, pEntityGameEvent);
        
        CreatedEvent(this, pGameEvent);
        return pGameEvent;
    }
    virtual GameEvent* Create(std::pair<unsigned char*, unsigned long>* pRawBytesPair)
    {
        assert(pRawBytesPair);
        
        GameEvent aGameEvent;
        GameEvent* pGameEvent = aGameEvent.New();
        
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
    virtual void Destroy(GameEvent*& pGameEvent)
    {
        DestroyedEvent(this, pGameEvent);
        delete pGameEvent;
        pGameEvent = NULL;
    }
    
    // Event(s)
    Poco::BasicEvent<GameEvent*&>    CreatedEvent;
    Poco::BasicEvent<GameEvent*&>    DestroyedEvent;
};

class EntityGameEventFactory :
    public FactoryT<GameEvent, EntityGameEvent_Dependencies>
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
