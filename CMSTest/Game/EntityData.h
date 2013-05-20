//
//  EntityData.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-15.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__EntityData__
#define __CMSTest__EntityData__

#include <string>
#include <limits.h>


//// Comment from:
//// http://msdn.microsoft.com/en-ca/library/windows/desktop/ms632660(v=vs.85).aspx
////
//template<typename DOUBLE, typename SINGLE>
//DOUBLE
//MAKE (const SINGLE lo, const SINGLE hi)
//{
//    static_assert (sizeof (DOUBLE) == (2 * sizeof (SINGLE)), "Unmatched");
//    return ((static_cast<DOUBLE> (hi) << (CHAR_BIT * sizeof (SINGLE))) | lo);
//}

class EntityData
{
private:

protected:

    
public:
    uint64_t        m_ui64Tag;
    std::string     m_strUUID;
    
    const uint64_t&     Tag = m_ui64Tag;
    const std::string&  UUID = m_strUUID;
    
    // Constructor(s)
    EntityData(uint64_t ui64Tag, std::string strUUID);
    
    // Destructor(s)
    ~EntityData();
};



#endif /* defined(__CMSTest__EntityData__) */
