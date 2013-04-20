//
//  Entity.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__Entity__
#define __CMSTest__Entity__

#include <string>


class AEntity
{
private:
    static uint64_t         s_ui64Count;
    
protected:
    enum EType
    {
        POD         = 0,
        BULLET      = 1,
        NUMTYPES    = 2
    };
    
    std::string             m_strUUID;
    uint64_t                m_ui64Tag;
    
    // Constructor(s)
    AEntity(const std::string& strUUID, uint64_t ui64Tag);
    //AEntity(EType eType, const std::string& strUUID);
    
public:
    // Destructor(s)
    virtual ~AEntity();

};


#endif /* defined(__CMSTest__Entity__) */
