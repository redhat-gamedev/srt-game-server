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
protected:
    b2BodyDef       m_ab2BodyDef;
    b2FixtureDef    m_ab2FixtureDef;

    // Constructor(s)
    AB2DBodyDefinition() {};

public:
    // Properties
    b2BodyDef&        BodyDef     = m_ab2BodyDef;
    b2FixtureDef&     FixtureDef  = m_ab2FixtureDef;
};

#endif /* defined(__CMSTest__AB2DBodyDefinition__) */
