#ifndef _H_ARKITSESSIONDELEGATE_H_
#define _H_ARKITSESSIONDELEGATE_H_

#if ARKIT_SUPPORT

#include <ARKit/ARKit.h>

@interface ARKitSessionDelegate : NSObject <ARSessionDelegate, ARSessionObserver> {
}

- (id)initWithGame:(void *)pSystem;

@end

#endif

#endif
