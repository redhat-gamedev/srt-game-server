//
//  Pod.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Pod__
#define __CMSTest__Pod__

#include "AEntity.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "../Shared/ACommand.h"
#include "../Commands/RawInputCommand.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>
#include <string>
#include <list>

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
    
protected:
    Rock2D::Timer*                      m_pBulletTimer;
    decaf::util::StlQueue<Bullet*>      m_BulletQueue;
    
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveQueue;
    decaf::util::StlQueue<b2Vec2>       m_b2v2ShootQueue;
    
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


#endif /* defined(__CMSTest__Pod__) */
