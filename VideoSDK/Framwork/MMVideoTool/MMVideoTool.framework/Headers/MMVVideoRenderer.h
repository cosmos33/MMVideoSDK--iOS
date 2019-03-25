//
//  MMVVideoRenderer.h
//  MMVideoTool
//
//  Created by 杨乃川 on 2018/6/1.
//

#import <Foundation/Foundation.h>
#import "MMVVideoProcessor.h"
#import "MMVVideoControl.h"
@import AVFoundation;

typedef NS_ENUM(NSInteger, MMVVideoRenderType) {
    MMVVideoRenderTypeMetalPetal,
    MMVVideoRenderTypeGPUImage
};

@class MMVVideoOptions, MMVRendererOptions;

NS_ASSUME_NONNULL_BEGIN

@protocol MMVVideoRenderDelegate<NSObject>

@optional;
- (void)videoRenderer:(id)renderer didStart:(BOOL)resume;
- (void)videoRenderer:(id)renderer didFinish:(BOOL)manually;
- (void)videoRenderer:(id)renderer progressingPercentage:(float)percentage time:(CMTime)time;
- (void)videoRenderer:(id)renderer statusDidChange:(MMVVideoControlStatus)status formerStatus:(MMVVideoControlStatus)formerStatus;
@end

@interface MMVVideoRenderer : NSObject

@property (nonatomic, assign) float volume;
@property (nonatomic, assign) BOOL mute;

@property (nonatomic, weak, nullable) id<MMVVideoRenderDelegate> delegate;

@property (nonatomic, assign, readonly) MMVVideoControlStatus status;

- (instancetype)initWithTargetView:(UIView *)renderedView options:(nullable MMVRendererOptions *)options NS_DESIGNATED_INITIALIZER;

- (void)installVideo:(NSURL *)localVideoURL NS_DEPRECATED_IOS(7_0, 7_0, "use installVideo:options: instead");

- (void)installVideo:(NSURL *)localVideoURL options:(nullable MMVVideoOptions *)options;

- (void)start;
- (void)stop;
- (void)reset;
- (void)pause;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

@interface MMVRendererOptions: NSObject
@property (nonatomic, assign) MMVVideoRenderType processorType;
@property (nonatomic, assign) NSInteger performedFrameRate;
@end

@interface MMVVideoOptions : NSObject
@property (nonatomic, assign) MMVVideoProcessorResizingMode  resizingMode;
@property (nonatomic, assign) MMVVideoProcessorVideoType videoType;
@end



NS_ASSUME_NONNULL_END
