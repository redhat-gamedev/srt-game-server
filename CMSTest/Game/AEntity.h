//
//  Entity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Entity__
#define __CMSTest__Entity__

#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>
#include <string>
#include <list>

namespace gameevent
{
    class EntityGameEvent;
}
class AB2DEntity;
class Player;


class AEntity
{
    friend class BulletFactory;
public:
    enum EType
    {
        POD         = 0,
        BULLET      = 1,
        NUMTYPES    = 2
    };

private:
    static uint64_t                         s_ui64Count;
    static std::list<Player*>               s_listPlayers;
    static std::list<Player*>               s_listPlayersSwap;
    
    //std::list<AEntity*>             m_listEntities;
    //std::list<AEntity*>             m_listEntitiesSwap;
    
protected:
    // Class(es)
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const AEntity::EType&>    CreatedEvent;
        Poco::BasicEvent<const AEntity::EType&>    RetrievedEvent;
        Poco::BasicEvent<const AEntity::EType&>    UpdatedEvent;
        Poco::BasicEvent<const AEntity::EType&>    DestroyedEvent;
    };

    class _Serializer
    {
    public:
        void Serialize(const AEntity* anEntity, gameevent::EntityGameEvent* pEntityGameEvent);
        void Deserialisze(const gameevent::EntityGameEvent* pEntityGameEvent, AEntity*& anEntity);
    };
    
    // Class data
    static decaf::util::StlQueue<AEntity*>          s_EntityQueue;
    
    std::string             m_strUUID;
    uint64_t                m_ui64Tag;
    AB2DEntity*             m_pB2DEntity;

    // Constructor(s)
    //AEntity(AB2DEntity* pB2DEntity, uint64_t ui64Tag);
    AEntity(const std::string& strUUID, uint64_t ui64Tag, AB2DEntity* pAB2DEntity  /* sink */);

public:
    // Class
    static _Serializer          Serializer;
    
    static void ClassSetup();
    static void ClassTeardown();
    
    static void AddPlayer(const std::string& strUUID);
    static void RemovePlayer(const std::string& strUUID);
    static void Update();

    // Security Event response
    static void OnSecurityRequestJoin(const void* pSender, const std::string& strUUID);
    static void OnSecurityRequestLeave(const void* pSender, const std::string& strUUID);
    
    // Messenger Event response
    static void HandleMessengerConsumerEventPublisherCreateEntityRequest(const void* pSender, const AEntity& anEntity);
    
    // Instance
    // Constructor(s)
    AEntity();
    AEntity(const std::string& strUUID, uint64_t ui64Tag);
    
    // Destructor(s)
    virtual ~AEntity();
    
    // Properties
    const std::string&      UUID = m_strUUID;
    const uint64_t&         Tag = m_ui64Tag;
    
    // Method(s)
    bool ThisUUIDIsAMatch(const std::string& strUUID);
};


#endif /* defined(__CMSTest__Entity__) */
