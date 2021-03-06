#pragma once

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


// Used in case windows is not defined
typedef unsigned long	DWORD;
typedef unsigned short	WORD;
typedef unsigned char	BYTE;
typedef char			TCHAR;
#if TARGET_OS_IPHONE
typedef unsigned long	HRESULT;
#endif
typedef unsigned long	HWND;
//typedef long			LARGE_INTEGER;
typedef long long		LONGLONG;
#ifndef BOOL
typedef signed char		BOOL;
#endif
#ifndef float32
typedef float           float32;
#endif
#ifndef NULL
#define NULL 0
#endif
