//
//  MMFaceRegister.h
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


typedef NS_ENUM (NSInteger, MMFaceRegistCapture)
{
    MMFaceRegistCaptureFront,
    MMFaceRegistCaptureUnFront,
    MMFaceRegistCaptureNormal,
};

typedef NS_ENUM (NSInteger, MMFaceRegist)
{
    MMFaceRegistFront,
    MMFaceRegistLeft,
    MMFaceRegistRight,
    MMFaceRegistTop,
    MMFaceRegistBottom,
};


@interface MMFaceRegistOptions : NSObject <NSCopying>

@property (nonatomic, assign) BOOL capture;

@property (nonatomic, assign) MMFaceRegistCapture registCapture;

@property (nonatomic, assign) MMCVImageOrientation orientation;

@end

@interface MMFaceRegistInfo : NSObject <NSCopying>

@property (nonatomic, readonly) MMFaceRegist regist;

@property (nonatomic, readonly) double pitch;
@property (nonatomic, readonly) double yaw;
@property (nonatomic, readonly) double roll;

@property (nonatomic, readonly) CGRect rect;

@property (nonatomic, readonly, copy) NSArray<NSValue *> *landmarks;

@property (nonatomic, readonly) NSData *feature;

@property (nonatomic, readonly, nullable) MMFaceFeature *faceFeature;

@property (nonatomic, readonly) MMFaceQuality featureQuality;

@property (nonatomic, readonly) CGFloat leftEyeCloseProb;

@property (nonatomic, readonly) CGFloat rightEyeCloseProb;

- (instancetype)init NS_UNAVAILABLE;

@end

@interface MMFaceRegistResult : NSObject

@property (nonatomic, readonly, copy ,nullable) NSArray <MMFaceRegistInfo *>* currentInfos;
@property (nonatomic, readonly, copy ,nullable) NSArray <MMFaceRegistInfo *>* cachedInfos;

@end

@interface MMFaceRegister : NSObject

@property (nonatomic,copy,readonly) NSURL *alignmentModelURL;
@property (nonatomic,copy,readonly) NSURL *attributeModelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMFaceRegistResult *)registInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (nullable MMFaceRegistResult *)registInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMFaceRegistOptions*)options;

- (void)reset;


@end

NS_ASSUME_NONNULL_END
