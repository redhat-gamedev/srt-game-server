// Various types for inclusion
// Author: Dion Picco 2003
// Author: Roddie Kieley 2008
#pragma once


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
#ifndef NULL
#define NULL 0
#endif

