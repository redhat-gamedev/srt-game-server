//
//  UserData.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-15.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef __CMSTest__UserData__
#define __CMSTest__UserData__

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

class UserData
{
private:

protected:

    
public:
    uint64_t        m_ui64Tag;
    std::string     m_strUUID;
    
    // Constructor(s)
    UserData(uint64_t ui64Tag, std::string strUUID);
    
    // Destructor(s)
    ~UserData();
};



#endif /* defined(__CMSTest__UserData__) */
