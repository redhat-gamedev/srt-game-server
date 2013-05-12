//
//  B2DPod.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "B2DPod.h"

B2DPod          B2DPod::Definition;


B2DPod::B2DPod()
{
    // Define the dynamic body. We set its position
    m_ab2BodyDef.type = b2_dynamicBody;
    m_ab2BodyDef.position.Set(0.0f, 0.0f);
    
    // Set the size of our shape
    m_ab2CircleShape.m_radius = 1.0f;
    
    // Set the fixture and use the shape
    m_ab2FixtureDef.density = 1.0f;
    m_ab2FixtureDef.friction = 0.3f;
    m_ab2FixtureDef.restitution = 0.3f;
    m_ab2FixtureDef.filter.groupIndex = -2;
    m_ab2FixtureDef.shape = &m_ab2CircleShape;
}