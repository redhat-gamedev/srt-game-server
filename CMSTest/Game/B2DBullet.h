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
class Bullet;


class B2DBullet :
    public AB2DEntity
{
    friend class Bullet;
    
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
    b2Vec2              m_b2v2InitialDirection;
    EntityData*         m_pEntityData;
    //Bullet*             m_pBullet;

    // Helper(s)

    
public:
    static _B2DDefinition        Definition;
    
    // Constructor(s)
    B2DBullet(const b2Vec2& b2v2Position, b2Vec2& b2v2Direction, EntityData* pEntityData);//, Bullet* pBullet);
    
    // Destructor(s)
    ~B2DBullet();
    
    // Callback(s)
    //void OnB2DBodyCreated(b2Body* pb2bBullet);
    //void OnB2DBodyCreated();
    //void OnB2DBodyDestroyed();

//    void CreateBullet();
//    void DestroyBullet();
};


#endif /* defined(__CMSTest__B2DBullet__) */
