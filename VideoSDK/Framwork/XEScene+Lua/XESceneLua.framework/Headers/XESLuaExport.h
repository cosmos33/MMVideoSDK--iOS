//
// Created by momo783 on 13/05/2018.
//

#ifndef XES_XESLUAEXPORT_H
#define XES_XESLUAEXPORT_H


#if (defined(WIN32) && defined(_WINDOWS)) || defined(WINRT) || defined(WP8)
#ifdef __MINGW32__
        #include <string.h>
    #endif

    #if defined(_USRLUASTATIC)
        #define XES_LUA_DLL
    #else
        #if defined(_USRLUADLL)
            #define XES_LUA_DLL     __declspec(dllexport)
        #else         /* use a DLL library */
            #define XES_LUA_DLL     __declspec(dllimport)
        #endif
    #endif

    /* Define NULL pointer value */
    #ifndef NULL
        #ifdef __cplusplus
            #define NULL    0
        #else
            #define NULL    ((void *)0)
        #endif
    #endif
#elif defined(_SHARED_)
#define XES_LUA_DLL     __attribute__((visibility("default")))
#else
#define XES_LUA_DLL
#endif

#if XES_DEBUG_LOG
#ifdef TOLUA_RELEASE
#undefine TOLUA_RELEASE
#endif
#else
#define TOLUA_RELEASE
#endif


#endif //XES_XESLUAEXPORT_H
