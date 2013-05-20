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

class b2Body;


class AEntity
{
private:
    static uint64_t         s_ui64Count;
    //static _EventPublisher          EventPublisher;
    
protected:
    class _EventPublisher
    {
    public:
        // Event(s)
//        Poco::BasicEvent<const std::string&>    CreatedEvent;
//        Poco::BasicEvent<const std::string&>    DestroyedEvent;
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
    b2Body*                 m_pb2Body;
    
    // Constructor(s)
    AEntity(const std::string& strUUID, uint64_t ui64Tag);
    
public:
    //static _EventPublisher          EventPublisher;
    //static const _EventPublisher&

//    const uint64_t&          Tag = m_ui64Tag;
    
    // Destructor(s)
    virtual ~AEntity();

    // Method(s)
    bool ThisUUIDIsAMatch(const std::string& strUUID);

    // Event Firing Method(s)
//    void FireCreatedEvent(const std::string& strUUID);
//    void FireDestroyedEvent(const std::string& strUUID);
    //virtual void FireCreatedEvent(const EntityData& anEntityData);
    //virtual void FireDestroyedEvent(const EntityData& anEntityData);
};


#endif /* defined(__CMSTest__Entity__) */
