//
//  MMGestureDetector.h
//  Pods
//
//  Created by YuAo on 11/14/16.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MMCVDetectionOptions.h"

@class MMObjectFeature;

NS_ASSUME_NONNULL_BEGIN

@interface MMObjectDetectionResult : NSObject <NSCopying>

@property (nonatomic,readonly) NSArray<MMObjectFeature *> *features;

@property (nonatomic,readonly) float scoreThreadhold;

@property (nonatomic,readonly) NSArray<MMObjectFeature *> *rawFeatures;

- (instancetype)initWithRawFeatures:(NSArray<MMObjectFeature *> *)rawFeatures scoreThreadhold:(float)scoreThreadhold;

@end

@interface MMObjectDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSArray<MMObjectFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (MMObjectDetectionResult *)detectFeaturesInPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (MMObjectDetectionResult *)detectFeaturesInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

@end

NS_ASSUME_NONNULL_END
