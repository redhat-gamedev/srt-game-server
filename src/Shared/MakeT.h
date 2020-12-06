#ifndef SRT_MakeT_h
#define SRT_MakeT_h

//   Copyright 2020 Roddie Kieley
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

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
