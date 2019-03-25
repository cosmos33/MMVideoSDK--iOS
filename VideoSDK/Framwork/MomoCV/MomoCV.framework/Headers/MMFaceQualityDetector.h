//
//  MMFaceQualityDetector.h
//  MomoCV
//
//  Created by MOMO on 2018/12/28.
//

#import <Foundation/Foundation.h>
#import "MMFaceQuality.h"
#import "MMFaceFeature.h"

NS_ASSUME_NONNULL_BEGIN


@interface MMFaceQualityInfo : NSObject <NSCopying>

//[0~1]
//default is -1
@property (nonatomic, assign, readonly) float qualityScore;

@property (nonatomic, assign, readonly) MMFaceQualityCode qualityCode;
@property (nonatomic, assign, readonly) MMFacePoseType poseType;
@property (nonatomic, assign, readonly) MMFaceOcclusionType occlusionType;
@property (nonatomic, assign, readonly) MMFaceLivenessType livenessType;
@property (nonatomic, assign, readonly) MMFaceMotionBlurType motionBlurType;

@property (nonatomic, assign, readonly) NSInteger trackID;

@property (nonatomic, assign, readonly) float spotRatio;
@property (nonatomic, assign, readonly) float brightness;
@property (nonatomic, assign, readonly) float clarity;

@property (nonatomic, assign, readonly) float spotScore;
@property (nonatomic, assign, readonly) float brightnessScore;
@property (nonatomic, assign, readonly) float clarityScore;
@property (nonatomic, assign, readonly) float motionBlurScore;

@end

@interface MMFaceQualityOptions : NSObject <NSCopying>

@property (nonatomic, assign) BOOL strictQualityDetect; //default is YES
@property (nonatomic, assign) BOOL livenessDetect;      //default is YES
@property (nonatomic, assign) BOOL motionBlurDetect;    //default is YES
@property (nonatomic, assign) BOOL faceOcclusionDetect; //default is YES

// [0~1]
//default is 0.5
@property (nonatomic, assign) float motionBlurResultThreshold;

@end

@interface MMFaceQualityDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *alignmentModelURL;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle
                                       error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSArray <MMFaceQualityInfo *>*)faceQualityInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer
                                                  strictQuality:(BOOL)isStrict
                                                   faceFeatures:(NSArray <MMFaceFeature *>*)faceFeatures;

- (NSArray <MMFaceQualityInfo *>*)faceQualityInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer
                                                 qualityOptions:(MMFaceQualityOptions * _Nullable)options
                                                   faceFeatures:(NSArray <MMFaceFeature *>*)faceFeatures;

@end

NS_ASSUME_NONNULL_END
