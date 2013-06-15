//
//  B2DBullet.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DBullet__
#define __CMSTest__B2DBullet__

#include "AB2DEntity.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"

class AEntity;


class B2DBullet :
    public AB2DEntity
{
private:
    
protected:
    class _B2DDefinition :
        public AB2DEntity::_AB2DDefinition
    {
        friend class B2DBullet;
        
    protected:
        b2CircleShape       m_ab2CircleShape;
        
    public:
        // Constructor(s)
        _B2DDefinition();
    };

    b2Vec2              m_b2v2InitialPosition;
    b2Vec2              m_b2v2InitialVelocity;

    // Helper(s)

    
public:
    static _B2DDefinition        Definition;
    
    // Constructor(s)
    B2DBullet(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity, b2Vec2& b2v2FiringDirection, AEntity* pBullet);
    
    // Destructor(s)
    ~B2DBullet();
    
    // Callback(s)
};


#endif /* defined(__CMSTest__B2DBullet__) */
