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

class B2DBullet;


class Bullet :
    public AEntity
{
private:
    static uint32_t         s_ui32Count;
    
protected:
    B2DBullet*              m_pB2DBullet;

public:
    // Constructor(s)
    Bullet(const std::string& strUUID, const b2Vec2& b2v2Position, b2Vec2& b2v2Direction);
    
    // Destructor(s)
    ~Bullet();
};

#endif /* defined(__CMSTest__Bullet__) */
