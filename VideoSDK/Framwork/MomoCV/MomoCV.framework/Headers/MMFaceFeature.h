//
//  MMFaceFeature.h
//  MomoCVDemo
//
//  Created by YuAo on 4/25/16.
//  Copyright © 2016 Momo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <GLKit/GLKit.h>
#import <simd/simd.h>
#import "MMFaceQuality.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const MMFaceFeatureMetadataSkinColorThresholdKey;

typedef NS_ENUM(NSInteger, MMFaceLandmarks2DType) {
    MMFaceLandmarks2DType68,
    MMFaceLandmarks2DType96,
    MMFaceLandmarks2DType104,
    MMFaceLandmarks2DType137
};

@interface MMFaceLandmarks2D: NSObject <NSCopying>

@property (readonly) NSUInteger pointCount;

@property (nonatomic, readonly) const simd_float2 *points NS_RETURNS_INNER_POINTER;

@property (nonatomic, copy, readonly) NSArray<NSValue *> *pointValues;

@property (nonatomic, readonly) CGSize imageSize;

@property (nonatomic, readonly) const simd_float2 *normalizedPoints NS_RETURNS_INNER_POINTER;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithPoints:(const simd_float2[_Nonnull])points count:(NSUInteger)count imageSize:(CGSize)imageSize;

@end

@interface MMFaceFeature : NSObject <NSCopying>

@property (nonatomic,readonly) NSInteger trackingIdentifier;

@property (nonatomic,readonly) CGRect bounds;

- (MMFaceLandmarks2D *)landmarksOfType:(MMFaceLandmarks2DType)type NS_SWIFT_NAME(landmarks(ofType:));

- (MMFaceFeature *)faceFeatureByUpdatingLandmarksOfType:(MMFaceLandmarks2DType)type landmarks:(MMFaceLandmarks2D *)landmarks NS_SWIFT_NAME(updatingLandmarks(ofType:landmarks:));

@property (nonatomic,readonly) double pitch;
@property (nonatomic,readonly) double yaw;
@property (nonatomic,readonly) double roll;

@property (nonatomic,readonly) BOOL isAppropriateForFaceIdentifying;

@property (nonatomic,readonly) MMFaceQuality quality;

@property (nonatomic, strong, readonly) NSData *feature;

@property (nonatomic,readonly) NSDictionary *metadata;

@property (nonatomic,readonly) CGSize imageSize;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

@interface MMFaceFeature (ThreeDimensional)

@property (nonatomic,readonly) GLKMatrix3 cameraMatrix;
@property (nonatomic,readonly) GLKMatrix3 rotationMatrix;

@property (nonatomic,readonly) GLKVector3 rotationVector;
@property (nonatomic,readonly) GLKVector3 translationVector;

@property (nonatomic,readonly) GLKMatrix4 projectionMatrix;

@property (nonatomic,readonly) GLKMatrix4 modelViewMatrix;

@end

@interface MMFaceFeature (FaceRigFeature)

@property (nonatomic,readonly) GLKVector3 facerigEulerVector;

@property (nonatomic,readonly) NSArray <NSNumber *> *facerigStates;

@end

@interface MMFaceFeature (Deprecated)

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks; //NSValue of CGPoints

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks96; //NSValue of CGPoints

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks68;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks87;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks104;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks137;

@end

FOUNDATION_EXPORT NSString * const MMFaceFeatureErrorDomain;

typedef NS_ERROR_ENUM(MMFaceFeatureErrorDomain, MMFaceFeatureError) {
    MMFaceFeatureErrorInvalidJSONObject = 1
};

@interface MMFaceFeature (JSON)

- (nullable instancetype)initWithJSONRepresentation:(id)JSONObject error:(NSError **)error;

- (id)JSONRepresentation;

@end

NS_ASSUME_NONNULL_END
