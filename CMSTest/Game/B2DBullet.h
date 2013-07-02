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
#include "Poco/BasicEvent.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"

class AEntity;


class B2DBullet :
    public AB2DEntity
{
public:
    class _Dependencies :
        public AB2DEntity::_AB2DDefinition
    {
    protected:
        const b2Vec2&           m_b2v2GunPosition;
        const b2Vec2&           m_b2v2GunVelocity;
        b2CircleShape           m_b2CircleShape;
        
    public:
        // Constructor
        _Dependencies(const b2Vec2& b2v2GunPosition, const b2Vec2& b2v2GunVelocity);
        
        // Destructor()
        ~_Dependencies() {};
    };
    
private:
    
protected:    

public:
    // Constructor(s)
    B2DBullet(_Dependencies& theDependencies);

    // Destructor(s)
    ~B2DBullet();

    // Method(s)
    void Fire(b2Vec2& b2v2FiringDirection);
};


#endif /* defined(__CMSTest__B2DBullet__) */
