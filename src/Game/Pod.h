#ifndef __SRT__Pod__
#define __SRT__Pod__

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
#include <box2d/box2d.h>
#include "../Commands/ACommand.h"
#include "../Commands/RawInputCommand.h"
#include "../Commands/DualStickRawInputCommand.h"
#include <Poco/BasicEvent.h>
#include <string>
#include <list>
#include <deque>
#include <mutex>

namespace Rock2D
{
    class Timer;
}
class Bullet;
class AB2DEntity;


class Pod :
    public AEntity
{
    friend class PodFactory;
    
private:
    static uint32_t         s_ui32Count;
    static int16_t          s_i16GroupCount;
    
    
protected:
    Rock2D::Timer*                      m_pBulletTimer;
    std::deque<Bullet*>                 m_BulletQueue;
    std::mutex                          m_BulletQueueMutex;

    std::deque<b2Vec2>                  m_b2v2MoveQueue;
    std::mutex                          m_b2v2MoveQueueMutex;
    std::deque<b2Vec2>                  m_b2v2ShootQueue;
    std::mutex                          m_b2v2ShootQueueMutex;
    
    int16_t                 m_i16GroupCount;
    
    // Helper(s)

public:
    // Event(s)
    static Poco::BasicEvent<Pod*&>    UpdatedEvent;
    
    // Constructor(s)
    Pod(_Dependencies& theDependencies);
    
    // Destructor(s)
    ~Pod();
    
    // Method(s)
    void Update();
    
    // Input Event response
    void HandleDualStickRawInputCommandFactoryCreatedEvent(const void* pSender, DualStickRawInputCommand*& pDualStickRawInputCommand);
    void HandleDualStickRawInputCommandFactoryDestroyedEvent(const void* pSender, DualStickRawInputCommand*& pDualStickRawInputCommand);
    void HandleDualStickRawInputCommandExecutedEvent(const void* pSender, const std::string& strUUID);
};


#endif /* defined(__SRT__Pod__) */
