//
//  MLCameraSource.h
//  MomoChat
//
//  Created by YuAo on 10/14/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

@import Foundation;
@import MLMediaFoundation;
@import FaceDecorationKit;
@import AVFoundation;
@import MLFilterKitMetalPetal;
#import "MLVideoProcessor.h"
#import "MLBeautySettings.h"
#import "MLMediaSource.h"
#import "MLColorEnhancemnet.h"

NS_ASSUME_NONNULL_BEGIN

typedef  NS_ENUM(NSUInteger, MLCameraSouceProcessorType){
    MLCameraSouceProcessorTypeGPUImage = 0,
    MLCameraSouceProcessorTypeMetalPetal
};

typedef NS_ENUM(NSUInteger, MLCameraSourceImageDetectOrientation) {
    MLCameraSourceImageDetectOrientationUp, //0
    MLCameraSourceImageDetectOrientationDown, // 180 deg rotation
    MLCameraSourceImageDetectOrientationLeft, // 90 deg CCW
    MLCameraSourceImageDetectOrientationRight // 90 deg CW
};

typedef NS_OPTIONS(NSUInteger, MLCameraSourceDetectorOption){
    MLCameraSourceDetectorOptionNone = 0,
    MLCameraSourceDetectorOptionFace = 1 << 0,
    MLCameraSourceDetectorOptionBody = 1 << 1,
    MLCameraSourceDetectorOptionExpression = 1 << 2,
    MLCameraSourceDetectorOptionObject = 1 << 3,
    MLCameraSourceDetectorOptionSegmetation = 1 << 4,
    MLCameraSourceDetectorOptionHandGesture = 1 << 5,
    MLCameraSourceDetectorOptionAll = NSUIntegerMax,
};

OBJC_EXTERN NSString *const kMLDecorationManagerDecorationFilterAddedNotification;
@interface MLCameraSourceVideoFrameBenchmark : NSObject <NSCopying>

@property (nonatomic,readonly) NSTimeInterval faceDetectionInterval;
@property (nonatomic,readonly) NSTimeInterval bodyDetectionInterval;
@property (nonatomic,readonly) NSTimeInterval expressionDetectionInterval;
@property (nonatomic,readonly) NSTimeInterval objectDetectionInterval;
@property (nonatomic,readonly) NSTimeInterval imageSegmentationInterval;
@property (nonatomic,readonly) NSTimeInterval handGestureInterval;
@property (nonatomic,readonly) NSTimeInterval cpuProcessingInterval;
@property (nonatomic,readonly) NSTimeInterval gpuProcessingInterval;

@end

@class MLCameraSource, CXBeautyConfiguration, MMFaceFeature,MMObjectFeature, MMBodyFeature, MMExpression,MMHandFeature;

@protocol MLCameraSourceRawVideoSampleBufferOutputDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;

@end

@interface MLCameraSourceSaveFaceFeatureOptions : NSObject

@property (nonatomic, assign) int uploadUserFeature;
@property (nonatomic, assign) BOOL uploadAsynchronously;
@property (nonatomic, assign) BOOL useFeatureStrict;
@property (nonatomic, assign) int uploadFeatureVersion;
@property (nonatomic, assign) int sampleSkipFrameCount;
@property (nonatomic, copy) NSArray  *uploadFeatureEulerAngles;

@end


@interface MLCameraSourceAnalyticsImage : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSData *data;

@property (nonatomic,copy,readonly) NSString *identifier;

@end

@interface MLCameraSourceAnalyticsParameters : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSDictionary *dictionaryRepresentation;

- (void)updateURL:(NSURL *)URL forImage:(MLCameraSourceAnalyticsImage *)image;

- (void)updateResourceIdentifier:(NSString *)resourceIdentifier forImage:(MLCameraSourceAnalyticsImage *)image;

@end

@protocol MLCameraSourceAnalyticsDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource logEventWithParameters:(MLCameraSourceAnalyticsParameters *)parameters images:(NSArray<MLCameraSourceAnalyticsImage *> *)images;

@end
@protocol MLCameraSourceFeatureDetectionDelegate <NSObject>

- (void)cameraSource:(MLCameraSource *)cameraSource
        faceFeatures:(NSArray <MMFaceFeature *> * _Nullable )faceFeatures
      objectFeatures:(NSArray <MMObjectFeature *> * _Nullable)objectFeatures
   facialExpressions:(NSArray <MMFacialExpression  *> *_Nullable)facialExpressions
         exporesions:(NSArray <MMExpression  *> *_Nullable)exporesions
        bodyFeatures:(NSArray <MMBodyFeature *> *_Nullable)bodyFeatures
        handFeatures:(NSArray <MMHandFeature *> *_Nullable)handFeatures;

- (void)cameraSource:(MLCameraSource *)cameraSource faceFeatureVideoInfo:(id)info timeStamp:(CMTime)time;
@end

@interface MLCameraSource : NSObject <MLMediaSource>

+ (nullable MLCameraSource *)activeCameraSource;

@property (nonatomic, strong) MLCameraSourceSaveFaceFeatureOptions *saveFaceOptions;
@property (nonatomic,readonly,nullable) NSArray *currentFaceFeatures;

@property (nonatomic,weak) id<MLCameraSourceRawVideoSampleBufferOutputDelegate> rawVideoSampleBufferOutputDelegate;

@property (nonatomic,weak) id<MLCameraSourceAnalyticsDelegate> analyticsDelegate;
@property (nonatomic, weak) id<MLCameraSourceFeatureDetectionDelegate> featureDetectionDelegate;
@property (nonatomic) NSTimeInterval minimumAnalyticsInterval;

@property (nonatomic,strong,readonly) MLCamera *camera;

@property (nonatomic,strong,readonly) MLAudioPrism *audioPrism;

 @property (nonatomic, assign) MLCameraSourceImageDetectOrientation imageDetectOrientation;

- (instancetype)init NS_UNAVAILABLE;

- (id)initWithSessionPreset:(NSString *)sessionPreset cameraPosition:(AVCaptureDevicePosition)cameraPosition;

- (id)initWithSessionPreset:(NSString *)sessionPreset cameraPosition:(AVCaptureDevicePosition)cameraPosition processorType:(MLCameraSouceProcessorType)processorType;

// Camera Controls
- (void)startCapturing;
- (void)stopCapturing;

- (void)rotateCamera;

// default , front YES,  back camera NOT support
- (void)mirrorVideo:(BOOL)enable;


- (void)changeCameraVideoOrientation:(AVCaptureVideoOrientation)orientation;

@property (nonatomic) AVCaptureVideoStabilizationMode preferredVideoStabilizationMode;

@property (nonatomic) NSInteger videoCaptureDeviceFrameRate;

@property (nonatomic) float videoZoomFactor;

@property (nonatomic) BOOL audioOutputEnabled;

@property (nonatomic,readonly) CGSize outputVideoFrameSize;

@property (nonatomic, assign) MLCameraSourceDetectorOption detectorOption;
// Effect Controls
@property (nonatomic, assign) BOOL beautyDisable;

@property (nonatomic) CGRect cropRegion;

@property (nonatomic) CGFloat outputScale;

@property (nonatomic,copy,nullable) MLBeautySettings *beautySettings;
@property (nonatomic,copy,nullable) MLFilterDescriptor *filterDescriptor;
@property (nonatomic, assign) float lookUpTableFilterIntensity;

@property (nonatomic) BOOL watermarkEnabled;

@property (nonatomic) BOOL dokiBeautyEnable;

@property (nonatomic, copy)  CXBeautyConfiguration*dokiConfiguration;

@property (nonatomic, strong) MLColorEnhancemnet *colorEnhancement;

- (void)addDecoration:(FDKDecoration *)decoration duration:(NSTimeInterval)duration positionType:(NSInteger)positionType;

- (void)addDecoration:(FDKDecoration *)decoration withIdentifier:(NSString *)identifier;

- (void)removeDecorationWithIdentifier:(NSString *)identifier;

- (NSArray<NSString *> *)decorationIdentifiers;

- (FDKDecoration *)decorationWithIdentifier:(NSString *)identifier;

@property (nonatomic,copy) NSArray<MLObjectTriggeredDecoration *> *objectTriggeredDecorations;

@property (nonatomic, copy) NSArray <MLMetalPetalNativeViewItem *> *renderedViewItems;

// Benchmarking
@property (atomic,copy) MLCameraSourceVideoFrameBenchmark *currentVideoFrameBenchmark;

// feedback
// for pixel
@property (nonatomic, copy, nullable) void (^faceBoundsFeedback)(CGRect faceBounds, CGSize bufferSize) ;

@end

@interface MLCameraSource (Analytics)

- (void)markBeautySettingsAdjustmentDone;

@end

NS_ASSUME_NONNULL_END
