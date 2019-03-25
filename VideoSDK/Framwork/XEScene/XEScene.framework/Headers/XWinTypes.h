/******************************************************************************

 @File         XWinTypes.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XWinTypes.

 @HISTORY:

******************************************************************************/
#ifndef _X_WIN_TYPES_H_
#define _X_WIN_TYPES_H_

#ifdef _DEBUG
#define X_DEBUG
#endif

#include <windows.h>
#include <DbgHelp.h>
#include <Shlwapi.h>

#include <tchar.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <malloc.h> // for _alloca
#include <stdio.h>
#include <time.h>
#include <stdarg.h>	
#include <io.h>
#include <string.h>
#include <new>
#include <sys/stat.h>
#include <wchar.h>

#pragma warning(disable : 4251)
#pragma warning(disable : 4355) // this used in base initializer list                                  
#pragma warning(disable : 4996)

//-------------------------------------------------------
//	base types
//-------------------------------------------------------

typedef unsigned __int8		xuint8;		
typedef unsigned __int16	xuint16;		
typedef unsigned __int32	xuint32;
typedef unsigned __int64	xuint64;
		
typedef	signed __int8		xint8;		
typedef signed __int16		xint16;		
typedef signed __int32 		xint32;		
typedef signed __int64		xint64;		

typedef float				xfloat32;		
typedef double				xfloat64;	

typedef char				xchar;
typedef unsigned __int16	xuchar;	
typedef unsigned __int8		xbyte;
typedef xuint32				xbool;

#define xtrue				1
#define xfalse				0

#ifdef X_PLATFORM_64
typedef xint64				xptrint;		
typedef xuint64				xuptrint;	
#else
typedef xint32				xptrint;		
typedef xuint32				xuptrint;	
#endif

//	File handle
typedef HANDLE				XFileHANDLE;
#define XMEM			: public XMemBase

#define X_FORCEINLINE	__forceinline
#define X_INLINE		inline
#define X_ALIGN(n)		__declspec(align(n))

#define Assert			ASSERT


#ifdef X_PLATFORM_64
#define XAlloca16( x )	((void *)((((xint64)_alloca( (x)+15 )) + 15) & ~15))
#else
#define XAlloca16( x )	((void *)((((xint32)_alloca( (x)+15 )) + 15) & ~15))
#endif


#define X_DLL_EXPORT	__declspec(dllexport)
#define X_DLL_IMPORT	__declspec(dllimport)

#define X_DLL_LOCAL

#define X_STDCALL		__stdcall

#endif	//	_X_WIN_TYPES_H_