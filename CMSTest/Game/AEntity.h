//
//  Entity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Entity__
#define __CMSTest__Entity__

#include "EntityData.h"
#include "Poco/BasicEvent.h"
#include <string>

//class b2Body;
class AB2DEntity;


class AEntity
{
private:
    static uint64_t         s_ui64Count;
    
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
        Poco::BasicEvent<const EntityData&>    CreatedEvent;
        Poco::BasicEvent<const EntityData&>    DestroyedEvent;
    };

    enum EType
    {
        POD         = 0,
        BULLET      = 1,
        NUMTYPES    = 2
    };
    
    std::string             m_strUUID;
    uint64_t                m_ui64Tag;
    AB2DEntity*             m_pB2DEntity;
//    b2Body*                 m_pb2Body;
    
//    class _Factory
//    {
//    public:
//        AEntity* Create(const EntityData& anEntityData, b2Vec2& b2v2Position, b2Vec2& b2v2Direction);
//        //void Create(const EntityData& anEntityData, Player* pPlayer);
//        
//        void Destroy(AEntity* pBullet);
//        //void Destroy(Player* pPlayer);
//    };
    
    // Constructor(s)
    AEntity(const std::string& strUUID, uint64_t ui64Tag, AB2DEntity* pAB2DEntity  /* sink */);

    // Destructor(s)
    virtual ~AEntity();
    
public:
    //static  _Factory                    Factory;
    //static _EventPublisher          EventPublisher;
    //static const _EventPublisher&

//    const uint64_t&          Tag = m_ui64Tag;
    

    // Method(s)
    bool ThisUUIDIsAMatch(const std::string& strUUID);

    // Event Firing Method(s)
//    void FireCreatedEvent(const std::string& strUUID);
//    void FireDestroyedEvent(const std::string& strUUID);
    //virtual void FireCreatedEvent(const EntityData& anEntityData);
    //virtual void FireDestroyedEvent(const EntityData& anEntityData);
};


#endif /* defined(__CMSTest__Entity__) */
