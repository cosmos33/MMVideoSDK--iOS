//
//  MMOpticalFlowMotionDetector.h
//  Pods
//
//  Created by YuAo on 3/4/17.
//
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMMotionFeature : NSObject <NSCopying>

@property (nonatomic,readonly) int globalAmount;

@property (nonatomic,readonly) int localAmount;

@property (nonatomic,readonly) BOOL isValid;

@end

@interface MMOpticalFlowMotionDetector : NSObject

- (void)reset;

- (MMMotionFeature *)updateWithPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
