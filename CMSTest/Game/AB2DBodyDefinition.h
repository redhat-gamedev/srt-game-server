//
//  AB2DBodyDefinition.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__AB2DBodyDefinition__
#define __CMSTest__AB2DBodyDefinition__

#include "../../../ThirdParty/box2d/Box2D/Box2D/Box2D.h"


class AB2DBodyDefinition
{
public:
    b2BodyDef       m_ab2BodyDef;
    b2FixtureDef    m_ab2FixtureDef;
    
public:
    // Constructor(s)
    AB2DBodyDefinition() {};
};

class B2DPod :
    public AB2DBodyDefinition
{
public:
    b2CircleShape       m_ab2CircleShape;

    // Constructor(s)
    B2DPod();
    
public:
    static B2DPod     Definition;
};

#endif /* defined(__CMSTest__AB2DBodyDefinition__) */
