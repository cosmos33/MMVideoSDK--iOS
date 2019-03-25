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

#import "AREngine.h"
#import "ARTexture.h"
#import "IXARSystem.h"
#import "ARKitSessionDelegate.h"
#import "ARKitSystem.h"
#import "ARKitUtil.h"
#import "XARKitAnchorManager.h"
#import "XARKitPlaneManager.h"

FOUNDATION_EXPORT double XESceneARVersionNumber;
FOUNDATION_EXPORT const unsigned char XESceneARVersionString[];

