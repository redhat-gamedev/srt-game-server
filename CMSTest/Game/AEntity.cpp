//
//  Entity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AEntity.h"
#include "AB2DEntity.h"
#include "../Application/Messenger.h"
#include "../Application/Messenger_Producer.h"
//#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include <assert.h>

AEntity::_Serializer        AEntity::Serializer;
uint64_t                    AEntity::s_ui64Count = 1;

using namespace gameevent;


void AEntity::_Serializer::Serialize(const AEntity* pEntity, gameevent::EntityGameEvent* pEntityGameEvent)
{
    pEntityGameEvent->set_uuid(pEntity->m_strUUID);
    pEntityGameEvent->set_entitytag(pEntity->m_ui64Tag);
}

void AEntity::_Serializer::Deserialisze(const gameevent::EntityGameEvent* pEntityGameEvent, AEntity*& pEntity)
{
    
    
}

// Constructor(s)
AEntity::AEntity()
{
    // Necessary due to xdispatch sync compile errors? /// rnk 061413
}

AEntity::AEntity(const std::string& strUUID, uint64_t ui64Tag) :
    m_strUUID(strUUID),
    m_ui64Tag(ui64Tag),
    m_pB2DEntity(NULL)
{
    // Used for incoming event notification
    // data store only...
}

AEntity::AEntity(const std::string& strUUID, uint64_t ui64Tag, AB2DEntity* pAB2DEntity /* sink */) :
    m_strUUID(strUUID),
    m_ui64Tag(ui64Tag),
    m_pB2DEntity(pAB2DEntity)
{
    assert(strUUID.size() > 0);
    assert(ui64Tag > 0);
    assert(pAB2DEntity);
    
    ++s_ui64Count;
}

// Destructor(s)
AEntity::~AEntity()
{
    //std::cout << "AEntity::~AEntity() " << m_ui64Tag << std::endl;

    if (m_pB2DEntity)
    {
        delete m_pB2DEntity;
        m_pB2DEntity = NULL;
    }
    
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

