//
//  MMBodyLandmarkDetector.h
//  Pods
//
//  Created by YuAo on 2/11/17.
//
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVFoundation.h>
#import "MMCVDetectionOptions.h"
#import "MMBodyJoint.h"

NS_ASSUME_NONNULL_BEGIN

/// https://challenger.ai/datasets/keypoint

@interface MMBodyFeature : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSArray<MMBodyJoint *> *joints;

- (instancetype)initWithJoints:(NSArray<MMBodyJoint *> *)joints;

@end

@interface MMBodyDetectionOptions: NSObject <NSCopying>

@property (nonatomic, assign) MMCVImageOrientation orientation;

@property (nonatomic, assign) BOOL detectStillImage; // NO

@property (nonatomic, assign) BOOL usesCPUOnly; // Default NO

@end

@interface MMBodyDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error;

- (nullable instancetype)initWithModelURL:(NSURL *)modelURL error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSArray<MMBodyFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (NSArray<MMBodyFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMBodyDetectionOptions *)options;

@end

NS_ASSUME_NONNULL_END
