//
//  UserData.cpp
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-15.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#include "UserData.h"


// Constructor(s)
UserData::UserData(uint64_t ui64Tag, std::string strUUID) :
    m_ui64Tag(ui64Tag),
    m_strUUID(strUUID)
{
    
}

// Destructor(s)
UserData::~UserData()
{
    m_ui64Tag = 0;
    m_strUUID.clear();
}
