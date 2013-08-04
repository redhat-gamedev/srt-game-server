//
//  Bullet.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Bullet__
#define __CMSTest__Bullet__

#include "AEntity.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include "Poco/BasicEvent.h"
#include <decaf/util/StlQueue.h>
#include <string>

namespace Rock2D
{
    class Timer;
}
class AB2DEntity;


class Bullet :
    public AEntity
{
    friend class Pod;
    friend class BulletFactory;

private:
    static uint32_t         s_ui32Count;
    
protected:
    bool                    m_bAlive;
    Rock2D::Timer*          m_pLifeTimer;
    
public:
    // Event(s)
    static Poco::BasicEvent<Bullet*&>    UpdatedEvent;
    
    // Constructor(s)
    Bullet(_Dependencies& theDependencies);
    
    // Destructor(s)
    ~Bullet();
    
    // Method(s)
    const bool Alive() { return m_bAlive; }
    void Fire(b2Vec2& b2v2FiringDirection);

    // Override(s)
    void Update();
};

#endif /* defined(__CMSTest__Bullet__) */
