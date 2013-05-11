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
#include <decaf/util/StlQueue.h>
#include <string>


class Bullet :
    public AEntity
{
private:
    static uint32_t         s_ui32Count;
    
protected:    
    decaf::util::StlQueue<b2Body*>      m_b2bBulletQueue;

    // Helper(s)
    void CreateBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction);

public:
    // Constructor(s)
    Bullet(const std::string& strUUID, const b2Vec2& b2v2Position, b2Vec2& b2v2Direction);
    
    // Destructor(s)
    ~Bullet();
    
    // Callback(s)
    void ReceiveBullet(b2Body* pb2bBullet);
};

#endif /* defined(__CMSTest__Bullet__) */
