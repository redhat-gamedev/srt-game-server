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
//#include "../Proto/GameEvent.pb.h"
//#include "../Proto/EntityGameEvent.pb.h"
#include <string>

//namespace google
//{
//    namespace protobuf
//    {
//        class Message;
//    }
//}
namespace gameevent
{
    class EntityGameEvent;
}
class AB2DEntity;


//class ISerializable
//{
//public:
//    void
//}
//
//
class AEntity
{
public:
    enum EType
    {
        POD         = 0,
        BULLET      = 1,
        NUMTYPES    = 2
    };

private:
    static uint64_t         s_ui64Count;
    
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
//        Poco::BasicEvent<const EntityData&>    CreatedEvent;
//        Poco::BasicEvent<const EntityData&>    DestroyedEvent;
        Poco::BasicEvent<const AEntity::EType&>    CreatedEvent;
        Poco::BasicEvent<const AEntity::EType&>    DestroyedEvent;
    };

    class _Serializer
    {
    public:
        void Serialize(const AEntity* anEntity, gameevent::EntityGameEvent* pEntityGameEvent);
        void Deserialisze(const gameevent::EntityGameEvent* pEntityGameEvent, AEntity*& anEntity);
    };
    
    std::string             m_strUUID;
    uint64_t                m_ui64Tag;
    AB2DEntity*             m_pB2DEntity;

    // Constructor(s)
    AEntity(const std::string& strUUID, uint64_t ui64Tag, AB2DEntity* pAB2DEntity  /* sink */);

public:
    static _Serializer          Serializer;

    // Constructor(s)
    AEntity() {};
    // Copy constructor
    //AEntity(const AEntity& anEntity);

    // Destructor(s)
    virtual ~AEntity();
    
    // Properties
    const std::string&      UUID = m_strUUID;
    const uint64_t&         Tag = m_ui64Tag;
    
    // Method(s)
    bool ThisUUIDIsAMatch(const std::string& strUUID);
//    AEntity* Clone() const { return new AEntity(m_strUUID, m_ui64Tag, m_pB2DEntity); };

};


#endif /* defined(__CMSTest__Entity__) */
