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
#include "../Proto/GameEvent.pb.h"
#include "../Proto/EntityGameEvent.pb.h"
#include <assert.h>

//AEntity::_EventPublisher    AEntity::EventPublisher;
uint64_t                    AEntity::s_ui64Count = 1;

using namespace gameevent;


//AEntity* AEntity::_Factory::Create(const EntityData& anEntityData)
//{
//    AEntity* pEntity = NULL;
//    
//    switch()
//    {
//    case POD:
//        pEntity = new Player();
//        break;
//    case BULLET:
//        pEntity = new Bullet();
//        break;
//    default:
//        assert(false);
//    }
//    
//    return pEntity;
//}

// Constructor(s)
AEntity::AEntity(const std::string& strUUID, uint64_t ui64Tag, AB2DEntity* pAB2DEntity /* sink */) :
    m_strUUID(strUUID),
    m_ui64Tag(ui64Tag),
    m_pB2DEntity(pAB2DEntity)//,
//    m_pb2Body(NULL)
{
    assert(strUUID.size() > 0);
    assert(ui64Tag > 0);
    assert(pAB2DEntity);
    
    ++s_ui64Count;

    //FireCreatedEvent(m_strUUID);
    //FireCreatedEvent(EntityData(ui64Tag, strUUID));
    
}

// Destructor(s)
AEntity::~AEntity()
{
    //std::cout << "AEntity::~AEntity() " << m_ui64Tag << std::endl;
    //FireDestroyedEvent(m_strUUID);
    //FireDestroyedEvent(EntityData(m_ui64Tag, m_strUUID));

    delete m_pB2DEntity;
    m_pB2DEntity = NULL;
    
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
