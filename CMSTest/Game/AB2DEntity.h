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

class EntityData;


class AB2DEntity
{
protected:
    class ADefinition
    {
    protected:
        b2BodyDef       m_ab2BodyDef;
        b2FixtureDef    m_ab2FixtureDef;
        
        // Constructor(s)
        ADefinition() {};
        
    public:
        // Properties
        b2BodyDef&        BodyDef     = m_ab2BodyDef;
        b2FixtureDef&     FixtureDef  = m_ab2FixtureDef;
    };
    
    b2Body*         m_pb2Body;
    
    // Constructor(s)
    AB2DEntity();
    
    // Destructor
    virtual ~AB2DEntity();
    
public:
    // Method(s)
    void SetEntityData(EntityData* pEntityData);
};



#endif /* defined(__CMSTest__AB2DEntity__) */
