//
//  Entity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AEntity.h"
#include "AB2DEntity.h"
#include "Player.h"
#include "PodFactory.h"
#include "B2DPodFactory.h"
#include "CommandConsumer.h"
#include "../Shared/ACommand.h"
#include "../Application/SecurityCommand.h"
#include "../Shared/FactoryT.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "Poco/FunctionDelegate.h"
//#include <iostream>
//#include <bitset>
#include <assert.h>

decaf::util::StlQueue<AEntity*>     AEntity::s_EntityQueue;
AEntity::_Serializer                AEntity::Serializer;
std::list<Player*>                  AEntity::s_listPlayers;
std::list<Player*>                  AEntity::s_listPlayersSwap;
uint64_t                            AEntity::s_ui64Count = 1;


// Constructor(s)
AEntity::_Dependencies::_Dependencies(const std::string& strUUID, AB2DEntity* pB2DEntity) :
    m_strUUID(strUUID),
    m_pB2DEntity(pB2DEntity)
{
    assert(strUUID.length() > 0);
    assert(pB2DEntity);
}

void AEntity::_Serializer::Serialize(const AEntity* pEntity, usx::geofactions::EntityGameEventBuffer* pEntityGameEvent)
{
    //using namespace std;
    using namespace box2d;
    using namespace usx::geofactions;
    
    assert(pEntityGameEvent);
    
    PbBody* pBody = NULL;

    pEntityGameEvent->set_uuid(pEntity->m_strUUID);
    pEntityGameEvent->set_entitytag(pEntity->m_ui64Tag);
    //EntityGameEvent* pEntityGameEvent = static_cast<EntityGameEvent*>(pMessage);
    //cout << hex << pEntityGameEvent->type() << endl;
//    if (pEntityGameEvent)
//    {
//        uint64_t ui64Tag = pEntityGameEvent->entitytag();
//        bitset<sizeof(uint64_t)*8>    aBitSet(ui64Tag);
//        //cout << hex << pEntityGameEvent->entitytag() << endl;
//        cout << aBitSet << endl;
//    }
    
    pBody = pEntityGameEvent->mutable_body();
    pEntity->m_pB2DEntity->Serializer.Serialize(pEntity->m_pB2DEntity, pEntityGameEvent);
}

void AEntity::_Serializer::Deserialisze(const usx::geofactions::EntityGameEventBuffer* pEntityGameEvent, AEntity*& pEntity)
{
    
    
}

//// Class
void AEntity::ClassSetup()
{
    //Security::EventPublisher.RequestJoinEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
    //Security::EventPublisher.RequestLeaveEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
    
    //CommandConsumer::Instance().EventConsumedEvent += Poco::FunctionDelegate<google::protobuf::Message*&>(&AEntity::HandleEventConsumedEvent);
    
    FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>&      theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theJoinSecurityCommandFactory.CreatedEvent += Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryCreated);
    theJoinSecurityCommandFactory.DestroyedEvent += Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryDestroyed);

    FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>&      theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theLeaveSecurityCommandFactory.CreatedEvent += Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryCreated);
    theLeaveSecurityCommandFactory.DestroyedEvent += Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryDestroyed);
}

void AEntity::ClassTeardown()
{
    //CommandConsumer::Instance().EventConsumedEvent -= Poco::FunctionDelegate<google::protobuf::Message*&>(&AEntity::HandleEventConsumedEvent);
    
    //Security::EventPublisher.RequestLeaveEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
    //Security::EventPublisher.RequestJoinEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
    
    FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>&      theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theJoinSecurityCommandFactory.DestroyedEvent -= Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryDestroyed);
    theJoinSecurityCommandFactory.CreatedEvent -= Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryCreated);
    
    FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>&      theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theLeaveSecurityCommandFactory.DestroyedEvent -= Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryDestroyed);
    theLeaveSecurityCommandFactory.CreatedEvent -= Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryCreated);
}

void AEntity::AddPlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    //    xdispatch::global_queue().sync([=]
    //    {
    
    B2DPodFactory& aB2DPodFactory = B2DPodFactory::Instance();
    PodFactory& aPodFactory = PodFactory::Instance();
    
    b2Vec2 b2v2Position;
    b2v2Position.x = 0.0f;
    b2v2Position.y = 0.0f;
    const b2Vec2& b2v2PositionRef = b2v2Position;
    B2DPod::_Dependencies aB2DPodDependencies(b2v2PositionRef);
    B2DPod* pB2DPod = aB2DPodFactory.Create(aB2DPodDependencies);
    
    Player::_Dependencies aPodDependencies(strUUID, pB2DPod);
    Player* pPlayer = aPodFactory.Create(aPodDependencies);
    s_listPlayers.push_front(pPlayer);
    
    //    });    
}

void AEntity::RemovePlayer(const std::string& strUUID)
{
    assert(strUUID.length() > 0);
    
    PodFactory& aPodFactory = PodFactory::Instance();
    
    //    xdispatch::global_queue().sync([=]
    //    {
    std::list<Player*>::iterator    iterPlayerList;
    Player* pPlayer = NULL;
    
    iterPlayerList = s_listPlayers.begin();
    for (;iterPlayerList != s_listPlayers.end(); iterPlayerList++)
    {
        pPlayer = *iterPlayerList;
        if (pPlayer->ThisUUIDIsAMatch(strUUID))
        {
            s_listPlayers.erase(iterPlayerList);
            aPodFactory.Destroy(pPlayer);
            break;
        }
    }
    //    });
}

void AEntity::Update()
{
    s_listPlayersSwap = s_listPlayers;
    Player*     pPlayer = NULL;
    while (!(s_listPlayersSwap.empty()))
    {
        pPlayer = s_listPlayersSwap.front();
        s_listPlayersSwap.pop_front();
        assert(pPlayer);
        pPlayer->Update();
    }
}

// Security::ICallbacks implementation
void AEntity::OnSecurityRequestJoin(const void* pSender, const std::string& strUUID)
{
    assert(!strUUID.empty());
    
    AddPlayer(strUUID);
}

void AEntity::OnSecurityRequestLeave(const void* pSender, const std::string& strUUID)
{
    assert(!strUUID.empty());
    
//    m_pSimulationSerialDispatchQueue->sync([=]
//    {
        RemovePlayer(strUUID);
//    });
}

// Event Consumer event response
//void AEntity::HandleEventConsumedEvent(const void* pSender, google::protobuf::Message*& pMessage)
//{
//    GameEvent* pGameEvent = NULL;
//    
//    pGameEvent = dynamic_cast<GameEvent*>(pMessage);
//}

//void AEntity::HandleSecurityCommandFactoryCreated(const void* pSender, SecurityCommand*& pSecurityCommand)
//{
//    assert(pSecurityCommand);
//    
//    pSecurityCommand->JoinedEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
//    pSecurityCommand->LeftEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
//}
//
//void AEntity::HandleSecurityCommandFactoryDestroyed(const void* pSender, SecurityCommand*& pSecurityCommand)
//{
//    assert(pSecurityCommand);
//    
//    pSecurityCommand->LeftEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
//    pSecurityCommand->JoinedEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
//}
void AEntity::HandleJoinSecurityCommandFactoryCreated(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
}

void AEntity::HandleJoinSecurityCommandFactoryDestroyed(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
}

void AEntity::HandleLeaveSecurityCommandFactoryCreated(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
}

void AEntity::HandleLeaveSecurityCommandFactoryDestroyed(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
}

//// Instance
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

