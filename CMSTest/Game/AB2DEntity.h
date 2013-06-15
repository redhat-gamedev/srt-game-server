//
//  AB2DEntity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__AB2DEntity__
#define __CMSTest__AB2DEntity__

#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"

class AEntity;


class AB2DEntity
{
    friend class AEntity;
    
protected:
    class _AB2DDefinition
    {
    protected:
        b2BodyDef       m_ab2BodyDef;
        b2FixtureDef    m_ab2FixtureDef;
        
        // Constructor(s)
        _AB2DDefinition();
        
    public:
        // Properties
        b2BodyDef&        BodyDef     = m_ab2BodyDef;
        b2FixtureDef&     FixtureDef  = m_ab2FixtureDef;
    };
    
    b2Body*         m_pb2Body;
    
    // Constructor(s)
    AB2DEntity(const _AB2DDefinition& aAB2DDefinition, AEntity* pEntity);
    
    // Destructor
    virtual ~AB2DEntity();
    
public:
    // Accessor(s)
    const b2Vec2& GetPosition() { return m_pb2Body->GetPosition(); }
    const b2Vec2& GetLinearVelocity() { return m_pb2Body->GetLinearVelocity(); }
    
    // Method(s)
    virtual void Move(float fX, float fY) {}
    virtual void Update() {}
};



#endif /* defined(__CMSTest__AB2DEntity__) */
