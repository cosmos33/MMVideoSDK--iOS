//
//  MMCoreMLBodyDetector.h
//  GPUImage
//
//  Created by Jackie on 2018/1/15.
//

#import <Foundation/Foundation.h>
#import "MMCVDetectionOptions.h"

@class MMBodyFeature;
@class MMBodyJoint;

NS_ASSUME_NONNULL_BEGIN

/// https://challenger.ai/datasets/keypoint

typedef NS_ENUM(NSUInteger, MMCoreMLBodyDetectModelVersion) {
    MMCoreMLBodyDetectModelVersionV1, // Output heat map raw and vector data raw
    MMCoreMLBodyDetectModelVersionV2, // Output heat map raw
    MMCoreMLBodyDetectModelVersionDefault = MMCoreMLBodyDetectModelVersionV1
};

@interface MMCoreMLBodyDetectOptions : NSObject

@property (nonatomic, assign) MMCVImageOrientation orientation; // UP

@property (nonatomic, assign) BOOL detectStillImage; // NO

@property (nonatomic, assign) BOOL cpuOnly; // Default NO

@property (nonatomic, assign) BOOL modelVersion; // Default V1


@end

API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0))
@interface MMCoreMLBodyDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelURL:(nullable NSURL *)url error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSArray<MMBodyFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;
- (NSArray<MMBodyFeature *> *)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMCoreMLBodyDetectOptions*)options;

@end


CF_EXTERN_C_BEGIN
CF_EXPORT void MMCVDrawJointConnectionInBGRAPixelBuffer(CVPixelBufferRef pixelBuffer, NSArray<MMBodyJoint *> *joints);
CF_EXTERN_C_END

NS_ASSUME_NONNULL_END
