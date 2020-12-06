//
//  Entity.h
//  SRT
//
//  Created by Roddie Kieley on 13-04-20.
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

//

#ifndef __SRT__Entity__
#define __SRT__Entity__

#include "../Proto/GameEventBuffer.pb.h"
#include "../Proto/EntityGameEventBuffer.pb.h"
#include <Poco/BasicEvent.h>
#include <decaf/util/StlQueue.h>
#include <string>
#include <list>

class AB2DEntity;
class Pod;
class JoinSecurityCommand;
class LeaveSecurityCommand;


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

    class _Dependencies
    {
    protected:
        const std::string&      m_strUUID;
        AB2DEntity*             m_pB2DEntity;
        
    public:
        // Constructor
        _Dependencies(const std::string& strUUID, AB2DEntity* pB2DEntity);
        
        // Destructor()
        ~_Dependencies() {};
        
        // Properties
        const std::string&      UUID = m_strUUID;
        AB2DEntity*&            pB2DEntity = m_pB2DEntity;
    };

private:
    static uint64_t                      s_ui64Count;
    static std::list<Pod*>               s_listPods;
    static std::list<Pod*>               s_listPodsSwap;
    
    //std::list<AEntity*>             m_listEntities;
    //std::list<AEntity*>             m_listEntitiesSwap;
    
protected:
    class _Serializer
    {
    public:
        void Serialize(const AEntity* anEntity, redhatgamedev::srt::EntityGameEventBuffer* pEntityGameEvent);
        void Deserialisze(const redhatgamedev::srt::EntityGameEventBuffer* pEntityGameEvent, AEntity*& anEntity);
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
    
    static void AddPod(const std::string& strUUID);
    static void RemovePod(const std::string& strUUID);
    static void Update();

    // Security Event response
    static void OnSecurityRequestJoin(const void* pSender, const std::string& strUUID);
    static void OnSecurityRequestLeave(const void* pSender, const std::string& strUUID);
    
    // Event Consumer event response
    static void HandleJoinSecurityCommandFactoryCreated(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand);
    static void HandleJoinSecurityCommandFactoryDestroyed(const void* pSender, JoinSecurityCommand*& pJoinSecurityCommand);
    static void HandleLeaveSecurityCommandFactoryCreated(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand);
    static void HandleLeaveSecurityCommandFactoryDestroyed(const void* pSender, LeaveSecurityCommand*& pLeaveSecurityCommand);
    
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


#endif /* defined(__SRT__Entity__) */
