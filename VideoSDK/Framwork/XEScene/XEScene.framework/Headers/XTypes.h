/******************************************************************************

 @File         XTypes.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XTypes.

 @HISTORY:

******************************************************************************/

#ifndef _X_TYPES_H_
#define _X_TYPES_H_

#include "XPlatform.h"

#if X_PLATFORM_WIN_DESKTOP
	#include "XWinTypes.h"
#elif X_PLATFORM_ANDROID
    #include "XAndroidTypes.h"
#elif X_PLATFORM_LINUX
	#include "XLinuxTypes.h"
#elif X_PLATFORM_XOS
    #include "XXOSTypes.h"
#endif

#define X_MIN_BYTE		0x00
#define X_MAX_BYTE		0xff
#define X_MIN_CHAR		0x80
#define X_MAX_CHAR		0x7f
#define X_MIN_UINT16	0x0000U
#define X_MAX_UINT16	0xffffU
#define X_MIN_UINT32	0x00000000U
#define X_MAX_UINT32	0xffffffffU
#define X_MIN_UINT64	0x0000000000000000ULL
#define X_MAX_UINT64	0xffffffffffffffffULL
#define X_MIN_INT16		0x8000
#define X_MAX_INT16		0x7fff
#define X_MIN_INT32		0x80000000
#define X_MAX_INT32		0x7fffffff
#define X_MIN_INT64		0x8000000000000000LL
#define X_MAX_INT64		0x7fffffffffffffffLL
#define X_MAX_FLT32		3.402823466e+38F
#define X_MIN_FLT32		1.175494351e-38F
#define X_EPSILON_FLT32 1.192092896e-07F
#define X_MAX_FLT64		1.7976931348623158e+308
#define X_MIN_FLT64		2.2250738585072014e-308
#define X_EPSILON_FLT64 2.2204460492503131e-016
#define X_FLOAT_NEAR_ZERO	0.001F

#define X_INDEX_NONE	 -1


#ifdef      MAX_PATH
#undef      MAX_PATH
#endif
#define     MAX_PATH        260


#define XBit( num )		( 1 << ( num ) )
#define XOffsetOf(s,m)   (xuint32)&reinterpret_cast<const volatile xbyte&>((((s *)0)->m))
#define XL(str)			L##str
#define X_SAFEDELETE(x) if ((x) != NULL) { delete x; x = NULL; }
#define X_SAFEDELETE_ARRAY(x) if ((x) != NULL) { delete[] x; x = NULL; }
#define X_SAFEFREE(x) if ((x) != NULL) { XMemory::Free(x); x = NULL; }

#ifdef X_PLATFORM_64
#define X_VOID_INT32( x ) ((xint32)((xuint64)(x) & 0xffffffff))
#define X_VOID_UINT32( x ) ((xuint32)((xuint64)(x) & 0xffffffff))
#else
#define X_VOID_INT32( x ) ((xint32)x)
#define X_VOID_UINT32( x ) ((xuint32)x)
#endif



#define X_SAFERELEASE(p) \
{ \
	if (p) \
	{ \
		(p)->Release(); \
		delete (p); \
		(p) = NULL; \
	} \
}

#define X_SAFERELEASE_INTERFACE(p) \
{ \
	if (p) \
	{ \
	(p)->Release(); \
	(p) = NULL; \
	} \
}

//	Text encoding.
enum XTextEncoding
{
	XTextEncodingUnknown = 0,	//	Unkown 
	XTextEncodingSystem,		//	The current Windows or Linux Code-Page. This is only for system-API calls, user should NOT save files or net-transfer the result buffer.
	XTextEncodingUTF8,
	XTextEncodingGB2312,
	XTextEncodingGB18030,
	XTextEncodingBig5,
	XTextEncodingNUM,			//	Number of supported encoding
};

// MessageBox enum
enum XMessageStyle
{
	XMessageStyle_OK = 0,		 
	XMessageStyle_OK_CANCLE,		
	XMessageStyle_YES_NO,	
};

enum XMessageReturn
{
	XMessageReturn_OK = 0,		 
	XMessageReturn_CANCLE,		
	XMessageReturn_NO,
	XMessageReturn_YES,
	XMessageReturn_OHTER
};


#ifndef ASSERT
#define ASSERT	assert
#endif	//	ASSERT

#if defined(_DEBUG) || defined(DEBUG)
#else
#undef ASSERT
#define ASSERT(x) 
#endif

//	Disable copy constructor and operator = 
#define DISABLE_COPY_AND_ASSIGNMENT(ClassName)	\
	private:\
	ClassName(const ClassName&);\
	ClassName& operator = (const ClassName&);

//	Time structure
struct XTIME
{
	xint32	year;		//	year since 1900
	xint32	month;		//	[0, 11]
	xint32	day;		//	[1, 31]
	xint32	hour;		//	[0, 23]
	xint32	minute;		//	[0, 59]
	xint32	second;		//	[0, 59]
	xint32	wday;		//	day of week, [0, 6]
};

#endif //	_X_TYPES_H_
