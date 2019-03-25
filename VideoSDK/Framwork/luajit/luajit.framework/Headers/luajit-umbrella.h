#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "lauxlib.h"
#import "lua.h"
#import "luaconf.h"
#import "luajit.h"
#import "lualib.h"

FOUNDATION_EXPORT double luajitVersionNumber;
FOUNDATION_EXPORT const unsigned char luajitVersionString[];

