//
//  MMObjectDetectorTrackingHelper.h
//  Pods
//
//  Created by YuAo on 3/16/17.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class MMObjectFeature,MMObjectTrackingOptions;

NS_ASSUME_NONNULL_BEGIN

@interface MMObjectDetectorTrackingHelper : NSObject

- (instancetype)initWithTrackingOptions:(MMObjectTrackingOptions *)options;

- (void)reset;

- (void)resetWithObjectFeature:(MMObjectFeature *)objectFeature trackingRegion:(CGRect)trackingRegion inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (nullable MMObjectFeature *)estimatedObjectFeatureByTrackingWithPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
