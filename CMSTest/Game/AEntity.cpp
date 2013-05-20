//
//  Entity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AEntity.h"
#include "../Application/Messenger.h"
#include "../Application/Messenger_Producer.h"
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"

//AEntity::_EventPublisher    AEntity::EventPublisher;
uint64_t                    AEntity::s_ui64Count = 1;

using namespace gameevent;


// Constructor(s)
AEntity::AEntity(const std::string& strUUID, uint64_t ui64Tag) :
    m_strUUID(strUUID),
    m_ui64Tag(ui64Tag),
    m_pb2Body(NULL)
{
    ++s_ui64Count;

    //FireCreatedEvent(m_strUUID);
    //FireCreatedEvent(EntityData(ui64Tag, strUUID));
    
//    std::string strPBBuffer = "";
//    
//    GameEvent* pGameEvent = new GameEvent();
//    EntityGameEvent* pEntityGameEvent = pGameEvent->mutable_entitygameevent();
//    assert(NULL != pEntityGameEvent);
//    
//    pGameEvent->set_type(GameEvent_GameEventType_ENTITY);
//    pEntityGameEvent->set_type(EntityGameEvent_EntityGameEventType_CREATE);
//    pEntityGameEvent->set_uuid(m_strUUID);
//    pEntityGameEvent->set_entitytag(ui64Tag);
//    
//    Messenger::Producer.Enqueue(pGameEvent);
}

// Destructor(s)
AEntity::~AEntity()
{
    //FireDestroyedEvent(m_strUUID);
    //FireDestroyedEvent(EntityData(m_ui64Tag, m_strUUID));

    m_strUUID.clear();
    m_ui64Tag = 0;
    --s_ui64Count;
}

// Method(s)
bool AEntity::ThisUUIDIsAMatch(const std::string& strUUID)
{
    if (strUUID == m_strUUID)
    {
        return true;
    }
    return false;
}

// Event Firing Method(s)
//void AEntity::FireCreatedEvent(const std::string& strUUID)
//void AEntity::FireCreatedEvent(const EntityData& anEntityData)
//{
//    //EventPublisher.CreatedEvent(this, strUUID);
//    EventPublisher.CreatedEvent(this, anEntityData);
//}
//
////void AEntity::FireDestroyedEvent(const std::string& strUUID)
//void AEntity::FireDestroyedEvent(const EntityData& anEntityData)
//{
//    //EventPublisher.DestroyedEvent(this, strUUID);
//    EventPublisher.DestroyedEvent(this, anEntityData);
//}
