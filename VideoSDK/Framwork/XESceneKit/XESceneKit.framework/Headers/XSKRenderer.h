//
//  XSKRenderer.h
//  Pods
//
//  Created by YuAo on 12/20/16.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT CGSize const XESOpenGLRendererPixelBufferPoolAutomaticPixelBufferSize;

@interface XSKRenderer : NSObject

+ (instancetype)rendererWithOptions:(nullable NSDictionary *)options;

@property (nonatomic) BOOL multisampleEnabled;

@property (nonatomic,readonly) BOOL usingPixelBufferPool;

- (void)setUsesPixelBufferPoolWithPixelBufferSize:(CGSize)size;

- (void)stopUsingPixelBufferPool;

- (CVPixelBufferRef)performRender:(void (^)(void))renderOperation atSize:(CGSize)size CF_RETURNS_NOT_RETAINED;

- (CVPixelBufferRef)performRender:(void (^)(void))renderOperation withInputBuffer:(nullable CVPixelBufferRef)inputBuffer atSize:(CGSize)size CF_RETURNS_NOT_RETAINED;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
