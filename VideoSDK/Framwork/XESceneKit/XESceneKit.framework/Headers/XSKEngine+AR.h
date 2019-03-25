//
//  XSKEngine+AR.h
//  XESceneKit
//
//  Created by momo783 on 16/08/2018.
//

#import <XESceneKit/XSKEngine.h>

@interface XSKEngine (AR)

- (BOOL)ARIsActive;

- (void)activeARSupport:(BOOL)active;

- (id)internalARSessionDelegate;

@end
