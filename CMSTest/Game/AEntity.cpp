//
//  Entity.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "AEntity.h"

uint64_t                    AEntity::s_ui64Count = 1;


// Constructor(s)
AEntity::AEntity(const std::string& strUUID, uint64_t ui64Tag) :
    m_strUUID(strUUID),
    m_ui64Tag(ui64Tag)
{
    ++s_ui64Count;
}

// Destructor(s)
AEntity::~AEntity()
{
    m_strUUID.clear();
    m_ui64Tag = 0;
    --s_ui64Count;
}