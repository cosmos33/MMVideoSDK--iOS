//
//  XSKDisplayView.h
//  XESceneKit
//
//  Created by wuzhijia on 2018/8/18.
//

#import <XESceneKit/XSKEngine.h>
#import "XSKTouchView.h"

@protocol XSKDisplayViewDelegate;

@interface XSKDisplayView : XSKTouchView


- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame;

@property (readonly) NSUInteger rendersSquence;

@property (weak) id <XSKDisplayViewDelegate> delegate;

- (void)setupEngine:(NSString *)path;
- (void)destoryEngine;

@end

@protocol XSKDisplayViewDelegate <NSObject>
@optional
- (void)displayView:(XSKDisplayView *)displayView willRender:(CGRect)renderRect;
- (void)displayView:(XSKDisplayView *)displayView customRender:(CGRect)renderRect;

@end
