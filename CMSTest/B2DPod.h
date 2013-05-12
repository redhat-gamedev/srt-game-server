//
//  B2DPod.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__B2DPod__
#define __CMSTest__B2DPod__

#include "AB2DBodyDefinition.h"


class B2DPod :
    public AB2DBodyDefinition
{
protected:
    b2CircleShape       m_ab2CircleShape;
    
    // Constructor(s)
    B2DPod();
    
public:
    static B2DPod     Definition;
};

#endif /* defined(__CMSTest__B2DPod__) */
