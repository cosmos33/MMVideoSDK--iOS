//
//  MMFaceScanner.h
//  Pods
//
//  Created by momo783 on 11/11/2017.
//
//

#import <Foundation/Foundation.h>
#import "MMFaceQuality.h"
#import "MMFaceFeature.h"
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface MMFaceScanInfo : NSObject <NSCopying>

@property (nonatomic, readonly) CGRect rect;

@property (nonatomic, readonly) CGRect stableRect;

@property (nonatomic, readonly) double pitch;
@property (nonatomic, readonly) double yaw;
@property (nonatomic, readonly) double roll;

@property (nonatomic, readonly, copy) NSArray<NSValue *> *landmarks;

@property (nonatomic, readonly) NSData *feature;

@property (nonatomic, readonly) MMFaceQuality featureQuality;

@property (nonatomic, readonly) CGFloat faceProb;

@property (nonatomic, readonly, nullable) MMFaceFeature *faceFeature;

// track ID
@property (nonatomic, readonly) NSInteger trackID;

//Only for track in Wowo Scanner
@property (nonatomic, readonly) NSInteger faceID;

@property (nonatomic, readonly) MMFacePoseType poseType;

- (instancetype)init NS_UNAVAILABLE;

@end

@interface MMFaceScannerOptions : NSObject <NSCopying>

@property (nonatomic, assign) NSInteger maxFaces;

@property (nonatomic, assign) MMCVImageOrientation orientation;

@property (nonatomic, assign) BOOL singleFrame;

@property (nonatomic, assign) BOOL featureStrict;

@property (nonatomic, assign) BOOL detectCorpCenter;

@property (nonatomic, assign) BOOL bigFeature;

@property (nonatomic, assign) BOOL photoNPD;    //静态图NPD参数

@property (nonatomic, assign) BOOL saveFeature; //default NO

@property (nonatomic, assign) double constraintPitch;

@property (nonatomic, assign) double constraintYaw;

@property (nonatomic, assign) double constraintRoll;

@property (nonatomic, assign) NSInteger faceAlignmentVersion;     // [0, 1, 2] // version 0 : 96 stable keypoints // version 1 : 96points add new eye points // version 2 : 137 points // default is 0

@end

@interface MMFaceScanner : NSObject

@property (nonatomic,copy,readonly) NSURL *alignmentModelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable NSArray<MMFaceScanInfo*> *)scanInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (nullable NSArray<MMFaceScanInfo*> *)scanInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMFaceScannerOptions*)options;

- (void)reset;

@end

NS_ASSUME_NONNULL_END
