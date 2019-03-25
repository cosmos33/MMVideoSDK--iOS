//
//  XXOSTypes.h
//
//
//
//

#ifndef _X_XOS_TYPES_H_
#define _X_XOS_TYPES_H_

#ifdef DEBUG
#define X_DEBUG
#endif


#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
//#include <malloc.h> // for _alloca
#include <stdio.h>
#include <time.h>
#include <stdarg.h>
//#include <io.h>
#include <string.h>
#include <new>
#include <sys/stat.h>
#include <wchar.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstddef>
//-------------------------------------------------------
//	base types
//-------------------------------------------------------

#include <stdint.h>
#include <wchar.h>
#include <stdarg.h>
#include <assert.h>
#include <alloca.h>
#include <locale.h>
#include <wctype.h>
#include <iconv.h>


//-------------------------------------------------------
//	base types
//-------------------------------------------------------
//#define XENGINE_IOS
typedef uint8_t				xuint8;
typedef uint16_t			xuint16;
typedef uint32_t			xuint32;
typedef uint64_t			xuint64;

typedef	int8_t				xint8;
typedef int16_t				xint16;
typedef int32_t 			xint32;
typedef int64_t				xint64;

typedef float				xfloat32;
typedef double				xfloat64;

typedef char				xchar;
typedef uint16_t			xuchar;
typedef uint8_t				xbyte;
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
typedef FILE*				XFileHANDLE;

#define XMEM /*: public XMemBase*/ //empty define XMEN

#define X_FORCEINLINE	inline __attribute__((always_inline))
#define X_INLINE		inline
#define X_ALIGN(n)		__attribute__((aligned(n)))

#define Assert			assert

#ifdef X_PLATFORM_64
#define XAlloca16( x )	((void *)((((xint64)alloca( (x)+15 )) + 15) & ~15))
#else
#define XAlloca16( x )	((void *)((((xint32)alloca( (x)+15 )) + 15) & ~15))
#endif


#define X_DLL_EXPORT	__attribute__((visibility("default")))
#define X_DLL_IMPORT
#define X_DLL_LOCAL		__attribute__((visibility("hidden")))

#define X_STDCALL

#if defined(__arm__)   // || defined(__arm64__)
#define ARM_NEON
#endif

#endif	//	_X_XOS_TYPES_H_
