//
//  XESDisplayView.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#import <UIKit/UIKit.h>

@protocol XESDisplayViewDelegate;
@interface XESDisplayView : UIView

- (instancetype)init NS_UNAVAILABLE;
- (instancetype)initWithFrame:(CGRect)frame;

@property (readonly) EAGLContext *context;
@property (readonly) NSUInteger rendersSquence;

@property (assign) id <XESDisplayViewDelegate> delegate;

- (CGSize)dispalySize;

- (void)setupEngine:(NSString *)path;
- (void)destoryEngine;

@end

@protocol XESDisplayViewDelegate <NSObject>
@optional
- (void)displayView:(XESDisplayView *)displayView willRender:(CGRect)renderRect;
- (void)displayView:(XESDisplayView *)displayView customRender:(CGRect)renderRect;

@end

