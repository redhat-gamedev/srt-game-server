//
//  Player.h
//  CMSTest
//
//  Created by Roddie Kieley on 12-12-15.
//  Copyright (c) 2012 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Player__
#define __CMSTest__Player__

#include "AEntity.h"
#include "../Proto/DualStick.pb.h"
#include "Poco/BasicEvent.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <decaf/util/StlQueue.h>
#include <string>
#include <list>

namespace Rock2D
{
    class Timer;
}
class Bullet;
//class B2DPod;


class Player :
    public AEntity
{
private:
    static uint32_t         s_ui32Count;
    
protected:
//    B2DPod*                 m_pB2DPod;
    
    Rock2D::Timer*                      m_pBulletTimer;
    decaf::util::StlQueue<Bullet*>      m_BulletQueue;
    
    decaf::util::StlQueue<b2Vec2>       m_b2v2ShootQueue;
    decaf::util::StlQueue<b2Vec2>       m_b2v2ShootSwapQueue;
    
    decaf::util::StlQueue<DualStick::PbDualStick>   m_PbDualStickQueue;
    

    // Helper(s)
    //void CreatePod();

public:
    static _EventPublisher          EventPublisher;
    
    // Constructor(s)
    Player(const std::string& strUUID);
    
    // Destructor(s)
    ~Player();
    
    // Method(s)
    void Update();
//    void CreatePod();
//    void DestroyPod();
    
    // Event Firing Method(s)
//    void FireCreatedEvent(const EntityData& anEntityData);
//    void FireDestroyedEvent(const EntityData& anEntityData);
    
    // Input Event response
    void OnInputDualStick(const void* pSender, DualStick::PbDualStick& aPbDualStick);
};


#endif /* defined(__CMSTest__Player__) */
