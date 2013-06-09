//
//  B2DPod.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DPod__
#define __CMSTest__B2DPod__

#include "AB2DEntity.h"
#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"
#include <decaf/util/StlQueue.h>

class EntityData;


class B2DPod :
    public AB2DEntity
{
protected:
    class _B2DDefinition :
        public AB2DEntity::_AB2DDefinition
    {
    protected:
        b2CircleShape       m_ab2CircleShape;
        
    public:
        // Constructor(s)
        _B2DDefinition();
    };
    
    EntityData*           m_pEntityData;
    
    decaf::util::StlQueue<b2Vec2>       m_b2v2MoveQueue;
    //decaf::util::StlQueue<b2Vec2>       m_b2v2MoveSwapQueue;
    
    // Helper(s)
    //void CreatePod();
    
public:
    static _B2DDefinition        Definition;
    
    // Constructor(s)
    B2DPod(EntityData* pEntityData);
    
    // Destructor(s)
    ~B2DPod();
    
    // Callback(s)
//    void OnB2DBodyCreated(b2Body* pb2bPod);
    
    // Method(s)
    void Move(float fX, float fY);
    void Update();
};

#endif /* defined(__CMSTest__B2DPod__) */
