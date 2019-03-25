//
//  MMFaceRecognizer.h
//  Pods
//
//  Created by Yu Ao on 29/01/2018.
//

#import <Foundation/Foundation.h>
#import "MMFaceFeature.h"
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface MMRawFaceInfo: NSObject <NSCopying>

- (NSData *)rawData;

- (instancetype)initWithRawData:(NSData *)data;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

@interface MMFaceIdentityFeature: NSObject <NSCopying>

@property (readonly) float *features;

@property (readonly) NSUInteger dimension;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

+ (float)cosineDistanceBetween:(MMFaceIdentityFeature *)featureA
                              :(MMFaceIdentityFeature *)featureB NS_SWIFT_NAME(cosineDistance(_:_:));

@end

@interface MMFaceRecognizerOptions : NSObject <NSCopying>

@property (nonatomic, assign) int bigFeaturesVersion; // 1 or 2

@property (nonatomic, assign) BOOL featureStrict;

//default is true;
// if you have ues FaceQuality before extract feature, please set false
@property (nonatomic, assign) BOOL qualityDetectSwitch;

@end

typedef NSString *MMFaceRecognizerModelType NS_EXTENSIBLE_STRING_ENUM;

FOUNDATION_EXPORT MMFaceRecognizerModelType MMFaceRecognizerModelTypeNormal;
FOUNDATION_EXPORT MMFaceRecognizerModelType MMFaceRecognizerModelTypeFast; //default

@interface MMFaceRecognizer : NSObject

@property (nonatomic, copy, readonly) NSURL *modelURL;

@property (nonatomic, readonly) NSInteger modelVersion;

// 仅提取大特征可以不用模型初始化
- (instancetype)init NS_DESIGNATED_INITIALIZER;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle
                                   modelType:(MMFaceRecognizerModelType)type
                                       error:(NSError **)error NS_DESIGNATED_INITIALIZER;

// Using pixelbuffer to output raw data. raw data could not use for face id directly,it contains image features using for further analysis.
- (NSArray <MMRawFaceInfo *>*)rawInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer
                                       faceFeatures:(NSArray <MMFaceFeature *>*)faceFeatures;

- (NSArray <MMRawFaceInfo *>*)rawInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer
                                       faceFeatures:(NSArray <MMFaceFeature *>*)faceFeatures
                                            options:(nullable MMFaceRecognizerOptions *)options;

// Directly get id feature from pixelbuffer and face feature, don't know if it quicker...
- (NSArray <MMFaceIdentityFeature *>*)featuresInPixelBuffer:(CVPixelBufferRef)pixelBuffer
                                               faceFeatures:(NSArray <MMFaceFeature *>*)faceFeatures;

- (MMFaceIdentityFeature *)featureFromRawInfo:(MMRawFaceInfo *)raw;

@end

NS_ASSUME_NONNULL_END

