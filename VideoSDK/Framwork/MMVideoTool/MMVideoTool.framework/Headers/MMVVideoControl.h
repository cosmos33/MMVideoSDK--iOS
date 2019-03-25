//
//  MMVVideoControl.h
//  MMVideoTool
//
//  Created by 杨乃川 on 2018/6/1.
//

#import <Foundation/Foundation.h>
typedef NS_ENUM(NSInteger, MMVVideoControlStatus) {
    MMVVideoControlStatusUnknown = 0,
    MMVVideoControlStatusPlaying = 1,
    MMVVideoControlStatusPaused = 2,
    MMVVideoControlStatusFinished = 3
};
@class MMVVideoControl, MMVVideoControlOption;
@import AVFoundation;
NS_ASSUME_NONNULL_BEGIN

@protocol MMVVideoControlDelegate<NSObject>
- (void)videoControl:(MMVVideoControl *)control progressingPercentage:(float)percentage time:(CMTime)time;
- (void)videoControl:(MMVVideoControl *)control finishedManually:(BOOL)manualOrNot;

- (void)videoControl:(MMVVideoControl *)control didStart:(BOOL)resume;
- (void)videoControl:(MMVVideoControl *)control statusDidChange:(MMVVideoControlStatus)status formerStatus:(MMVVideoControlStatus)formerStatus;
@end

@interface MMVVideoControl : NSObject

@property (nonatomic, assign) float volume;
@property (nonatomic, assign) BOOL mute;

@property (nonatomic, weak) id<MMVVideoControlDelegate> delegate;
@property (nonatomic, assign, readonly) MMVVideoControlStatus status;

- (instancetype)initWithOption:(nullable MMVVideoControlOption *)option;

- (void)videoFameBufferFeedback:(void(^)(CVPixelBufferRef pixelBuffer))feedback;

- (void)installVideo:(NSURL *)localVideoURL;

- (void)start;
- (void)stop;
- (void)reset;
- (void)pause;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (void)invalidateDisplayLink;
@end

@interface MMVVideoControlOption: NSObject
@property (nonatomic, assign) NSInteger performedFrameRate;
@end

NS_ASSUME_NONNULL_END
