//
//  AB2DEntity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-05-12.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AB2DEntity.h"
#include "B2DWorld.h"
#include "../../../ThirdParty/xdispatch/include/xdispatch/dispatch.h"

// Constructor(s)
AB2DEntity::AB2DEntity() :
    m_pb2Body(NULL)
{
    
}

// Destructor
AB2DEntity::~AB2DEntity()
{
}

// Method(s)
void AB2DEntity::SetEntityData(EntityData *pEntityData)
{
    assert(m_pb2Body);
    assert(pEntityData);
    
    m_pb2Body->SetUserData(pEntityData);
}
