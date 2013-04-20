//
//  MakeT.h
//  CMSTest
//
//  Created by Roddie Kieley on 13-04-20.
//  Copyright (c) 2013 Roddie Kieley. All rights reserved.
//

#ifndef CMSTest_MakeT_h
#define CMSTest_MakeT_h

#include <limits.h>


// Comment from:
// http://msdn.microsoft.com/en-ca/library/windows/desktop/ms632660(v=vs.85).aspx
//
template<typename DOUBLE, typename SINGLE>
DOUBLE
MakeT (const SINGLE lo, const SINGLE hi)
{
    static_assert (sizeof (DOUBLE) == (2 * sizeof (SINGLE)), "Unmatched");
    return ((static_cast<DOUBLE> (hi) << (CHAR_BIT * sizeof (SINGLE))) | lo);
}



#endif
