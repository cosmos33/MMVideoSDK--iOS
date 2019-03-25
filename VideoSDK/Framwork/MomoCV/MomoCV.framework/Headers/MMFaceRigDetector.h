//
//  MMFaceRigDetector.h
//  Pods
//
//  Created by momo783 on 21/08/2017.
//
//

#import <Foundation/Foundation.h>
#import "MMFaceFeature.h"
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MMFaceRigMeanFaceDetection) {
    MMFaceRigMeanFaceDetectionNone = -1,
    MMFaceRigMeanFaceDetectionSuccess = 0,
    MMFaceRigMeanFaceDetectionLoadFailed = 1,
    MMFaceRigMeanFaceDetectionNoFace = 2,
    MMFaceRigMeanFaceDetectionEyeClosing = 3,
    MMFaceRigMeanFaceDetectionPoseError = 4,
    MMFaceRigMeanFaceDetectionFarAway = 5,
    MMFaceRigMeanFaceDetectionTooClose = 6,
    MMFaceRigMeanFaceDetectionFailed = 7,
};

@interface MMFaceRigFeature : NSObject

@property (nonatomic, readonly) BOOL shouldDetectMeanFace;

@property (nonatomic, readonly) MMFaceRigMeanFaceDetection meanFaceDetection;

@property (nonatomic, readonly) NSArray <MMFaceFeature *> *features;

@end

@interface MMFaceRigDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *facerigModelURL;

@property (nonatomic,copy,readonly) NSURL *alignmentModelURL;
@property (nonatomic,copy,readonly) NSURL *detectionModelURL;


+ (BOOL)validateModelBundle:(NSBundle *)bundle;
	
- (instancetype)init NS_UNAVAILABLE;
	
- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (void)setFaceRigFeatures:(NSData *)features;

// Detector Mean Face
- (MMFaceRigMeanFaceDetection)detectMeanFaceForPiexlBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (MMFaceRigFeature *)facerigFeatureInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (nullable NSData *)getFaceRigFeatures;

@end


@interface MMFaceRigV2Detector : NSObject

@property (nonatomic,copy,readonly) NSURL *facerigModelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (MMFaceRigFeature *)facerigFeatureInPixelBuffer:(CVPixelBufferRef)pixelBuffer faceFeature:(MMFaceFeature*)faceFeature orientation:(MMCVImageOrientation)orientation;

@end

NS_ASSUME_NONNULL_END
