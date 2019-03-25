/******************************************************************************

 @File         XPlatform.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XPlatform.

 @HISTORY:

******************************************************************************/
#ifndef _X_PLATFORM_H_
#define _X_PLATFORM_H_

//Platform Defines
#if defined(_MSC_VER) 

#if defined(WINRT)

#else
#define X_PLATFORM_WIN_DESKTOP 1
#endif

#if defined(_WIN64)
#define X_PLATFORM_64 1
#elif defined(_WIN32)
#define X_PLATFORM_32 1
#endif

#elif defined(__ANDROID__)
//Attention: "__linux__" is also defined on Android platform.
#define X_PLATFORM_ANDROID 1

#if defined(__x86_64__) || defined(__aarch64__)
#define X_PLATFORM_64 1
#else
#define X_PLATFORM_32 1
#endif

#elif defined(__linux__)

#define X_PLATFORM_LINUX 1

#if defined(__x86_64__)
#define X_PLATFORM_64 1
#else
#define X_PLATFORM_32 1
#endif


#elif defined(__APPLE__)

#define X_PLATFORM_XOS 1


#if defined(__x86_64__) || defined(__arm64__)
#define X_PLATFORM_64 1
#else
#define X_PLATFORM_32 1
#endif

#endif


#ifdef __cplusplus
#define X_BEGIN_EXTERN_C	extern "C" {
#define X_END_EXTERN_C      }
#define X_EXTERN_C			extern "C"
#else
#define X_BEGIN_EXTERN_C
#define X_END_EXTERN_C
#define X_EXTERN_C
#endif

#endif //_X_PLATFORM_H_

