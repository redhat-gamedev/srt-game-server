//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include "AEntity.h"
#include "AB2DEntity.h"
#include "Pod.h"
#include "PodFactory.h"
#include "B2DPodFactory.h"
#include "../Commands/CommandConsumer.h"
#include "../Commands/ACommand.h"
#include "../Commands/SecurityCommand.h"
#include "../Commands/JoinSecurityCommand.h"
#include "../Commands/LeaveSecurityCommand.h"
#include "../Shared/FactoryT.h"
#include <box2d/box2d.h>
#include <Poco/FunctionDelegate.h>
#include <assert.h>
#include "../Logging/loguru.hpp"

std::queue<AEntity*>            AEntity::s_EntityQueue;
AEntity::_Serializer            AEntity::Serializer;
std::list<Pod*>                 AEntity::s_listPods;
std::list<Pod*>                 AEntity::s_listPodsSwap;
uint64_t                        AEntity::s_ui64Count = 1;


// Constructor(s)
AEntity::_Dependencies::_Dependencies(const std::string& strUUID, AB2DEntity* pB2DEntity) :
    m_strUUID(strUUID),
    m_pB2DEntity(pB2DEntity)
{
    assert(strUUID.length() > 0);
    assert(pB2DEntity);
}

void AEntity::_Serializer::Serialize(const AEntity* pEntity, redhatgamedev::srt::EntityGameEventBuffer* pEntityGameEvent)
{
    using namespace box2d;
    using namespace redhatgamedev::srt;
    
    assert(pEntityGameEvent);
    
    PbBody* pBody = NULL;

    pEntityGameEvent->set_uuid(pEntity->m_strUUID);
    pEntityGameEvent->set_entitytag(pEntity->m_ui64Tag);

    pBody = pEntityGameEvent->mutable_body();
    pEntity->m_pB2DEntity->Serializer.Serialize(pEntity->m_pB2DEntity, pEntityGameEvent);
}

void AEntity::_Serializer::Deserialisze(const redhatgamedev::srt::EntityGameEventBuffer* pEntityGameEvent, AEntity*& pEntity)
{
    
    
}

//// Class
void AEntity::ClassSetup()
{
    auto& theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    auto& theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theJoinSecurityCommandFactory.CreatedEvent += Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryCreated);
    theJoinSecurityCommandFactory.DestroyedEvent += Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryDestroyed);
    
    theLeaveSecurityCommandFactory.CreatedEvent += Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryCreated);
    theLeaveSecurityCommandFactory.DestroyedEvent += Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryDestroyed);
}

void AEntity::ClassTeardown()
{
    auto& theJoinSecurityCommandFactory = FactoryT<JoinSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    auto& theLeaveSecurityCommandFactory = FactoryT<LeaveSecurityCommand, SecurityCommand::_SecurityDependencies>::Instance();
    
    theJoinSecurityCommandFactory.DestroyedEvent -= Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryDestroyed);
    theJoinSecurityCommandFactory.CreatedEvent -= Poco::FunctionDelegate<JoinSecurityCommand*&>(&AEntity::HandleJoinSecurityCommandFactoryCreated);
    
    theLeaveSecurityCommandFactory.DestroyedEvent -= Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryDestroyed);
    theLeaveSecurityCommandFactory.CreatedEvent -= Poco::FunctionDelegate<LeaveSecurityCommand*&>(&AEntity::HandleLeaveSecurityCommandFactoryCreated);
}

void AEntity::AddPod(const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(4);
    assert(strUUID.length() > 0);
    
    B2DPodFactory& aB2DPodFactory = B2DPodFactory::Instance();
    PodFactory& aPodFactory = PodFactory::Instance();
    
    b2Vec2 b2v2Position;
    b2v2Position.x = 0.0f;
    b2v2Position.y = 0.0f;
    const b2Vec2& b2v2PositionRef = b2v2Position;
    B2DPod::_Dependencies aB2DPodDependencies(b2v2PositionRef);
    B2DPod* pB2DPod = aB2DPodFactory.Create(aB2DPodDependencies);
    
    Pod::_Dependencies aPodDependencies(strUUID, pB2DPod);
    Pod* pPod = aPodFactory.Create(aPodDependencies);
    s_listPods.push_front(pPod);
}

void AEntity::RemovePod(const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(4);
    assert(strUUID.length() > 0);
    
    PodFactory& aPodFactory = PodFactory::Instance();
    std::list<Pod*>::iterator    iterPodList;
    Pod* pPod = NULL;
    
    iterPodList = s_listPods.begin();
    for (;iterPodList != s_listPods.end(); iterPodList++)
    {
        pPod = *iterPodList;
        if (pPod->ThisUUIDIsAMatch(strUUID))
        {
            s_listPods.erase(iterPodList);
            aPodFactory.Destroy(pPod);
            break;
        }
    }
}

void AEntity::Update()
{
    LOG_SCOPE_FUNCTION(4);
    LOG_SCOPE_F(4, "Doing the AEntity update");
    s_listPodsSwap = s_listPods;
    Pod*     pPod = NULL;
    
    while (!(s_listPodsSwap.empty()))
    {
        pPod = s_listPodsSwap.front();
        s_listPodsSwap.pop_front();
        assert(pPod);
        LOG_F(3, "Updating a specific Pod");
        pPod->Update();
    }
}

// Security::ICallbacks implementation
void AEntity::OnSecurityRequestJoin(const void* pSender, const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(4);
    assert(!strUUID.empty());
    
    AddPod(strUUID);
}

void AEntity::OnSecurityRequestLeave(const void* pSender, const std::string& strUUID)
{
    LOG_SCOPE_FUNCTION(4);
    assert(!strUUID.empty());
    
    RemovePod(strUUID);
}

void AEntity::HandleJoinSecurityCommandFactoryCreated(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    LOG_SCOPE_FUNCTION(4);
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
}

void AEntity::HandleJoinSecurityCommandFactoryDestroyed(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand)
{
    LOG_SCOPE_FUNCTION(4);
    assert(pJoinSecurityCommand);
    
    pJoinSecurityCommand->ExecutedEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestJoin);
}

void AEntity::HandleLeaveSecurityCommandFactoryCreated(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    LOG_SCOPE_FUNCTION(4);
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent += Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
}

void AEntity::HandleLeaveSecurityCommandFactoryDestroyed(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand)
{
    LOG_SCOPE_FUNCTION(4);
    assert(pLeaveSecurityCommand);
    
    pLeaveSecurityCommand->ExecutedEvent -= Poco::FunctionDelegate<const std::string&>(&AEntity::OnSecurityRequestLeave);
}

//// Instance
// Constructor(s)
AEntity::AEntity()
{

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
