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

class EntityData;


class B2DBullet :
    public AB2DEntity
{
private:
    
protected:
    class _Definition :
        public AB2DEntity::ADefinition
    {
    protected:
        b2CircleShape       m_ab2CircleShape;
        
    public:
        // Constructor(s)
        _Definition();
    };

    b2Vec2              m_b2v2InitialPosition;
    b2Vec2              m_b2v2InitialDirection;
    EntityData*           m_pEntityData;

    // Helper(s)
    void CreateBullet();
    
public:
    static _Definition        Definition;
    
    // Constructor(s)
    B2DBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction, EntityData* pEntityData);
    
    // Destructor(s)
    ~B2DBullet();
    
    // Callback(s)
    void OnB2DBodyCreated(b2Body* pb2bBullet);
};


#endif /* defined(__CMSTest__B2DBullet__) */
