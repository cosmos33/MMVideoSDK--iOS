//
//  MDMomentRecordHandler.m
//  MDChat
//
//  Created by wangxuan on 17/1/18.
//  Copyright © 2017年 sdk.com. All rights reserved.
//

#import "MDMomentRecordHandler.h"
#import "MDFaceDecorationFileHelper.h"
#import "MDFaceTipItem.h"
#import "MDFaceTipManager.h"
#import "UIConst.h"
#import "MDRecordContext.h"

//AI美颜
//#import "MLRoomDecorationDataSource.h"

#import "MDBeautySettings.h"
#import "MDRecordingAdapter+MDAudioPitch.h"
@import RecordSDK;

#define kDefaultRecordBitRate   (5.0 * 1024 * 1024)

static AVCaptureSession *__weak MDTimelineRecordViewControllerCurrentCaptureSession = nil;

@interface MDMomentRecordHandler ()
<
    MDFaceTipShowDelegate
>

@property (atomic,    strong) MDFaceTipManager      *faceTipManager;

//@property (nonatomic, strong) MDCameraEditorContext *context;
//@property (nonatomic, strong) MDCameraRenderPipline *renderPipline;
@property (nonatomic, strong) MDRecordingAdapter *adapter;

@end

@implementation MDMomentRecordHandler

- (MDRecordingAdapter *)adapter {
    if (!_adapter) {
        _adapter = [[MDRecordingAdapter alloc] initWithToken:@""];
    }
    return _adapter;
}

- (void)dealloc {
    //清理gpu和变脸资源缓存
    [self cleanCache];
}

- (instancetype)initWithContentView:(UIView *)containerView
                  maxRecordDuration:(NSTimeInterval)maxDuration
                     cameraPosition:(AVCaptureDevicePosition)position
                        openXengine:(BOOL)isOpen {
    self = [super init];
    if (self) {
        NSAssert(maxDuration != 0, @"max Duration is 0");
        
        // 相机设置
        MDRecordingAdapter *adapter = self.adapter;
        [adapter setVideoCodecKey:AVVideoCodecH264];
        
        float recordBitRate = 0.0;
        if (isFloatEqual(recordBitRate, 0.0)) {
            recordBitRate = kDefaultRecordBitRate;
        }
        
        [adapter setVideoBitRate:recordBitRate];
        [adapter setVideoResolution:CGSizeMake(720, 1280)];
        [adapter setVideoScaleMode:AVVideoScalingModeResizeAspectFill];
        [adapter setCameraPreset:AVCaptureSessionPreset1280x720];
        [adapter setCameraPosition:position];
        
        [adapter setupRecorder];
//        [adapter setMaxRecordDuration:maxDuration];
        self.recordDuration = maxDuration;

        __weak typeof(self) weakself = self;
        adapter.detectFace = ^(BOOL tracking) {
            // 变脸提示
            [weakself updateFaceTipWithAFaceFeature:tracking];
        };

        UIView<MLPixelBufferDisplay> *previewView = adapter.previewView;
        previewView.frame = containerView.frame;
        [containerView addSubview:previewView];
        
        [self downloadCXMakeupBundleIfNeeded];
        
        // 启动3D引擎
        if (!isOpen) {
            [adapter runXESEngineWithDecorationRootPath:[MDFaceDecorationFileHelper FaceDecorationBasePath]];
        }
    }
    
    return self;
}

- (instancetype)initWithContentView:(UIView *)containerView maxRecordDuration:(NSTimeInterval)maxDuration {
    return [self initWithContentView:containerView maxRecordDuration:maxDuration cameraPosition:AVCaptureDevicePositionUnspecified];
}

- (instancetype)initWithContentView:(UIView *)containerView maxRecordDuration:(NSTimeInterval)maxDuration cameraPosition:(AVCaptureDevicePosition)pisition {
    return [self initWithContentView:containerView maxRecordDuration:maxDuration cameraPosition:pisition openXengine:YES];
}

- (void)setRecordDuration:(NSTimeInterval)recordDuration {
    [self.adapter setMaxRecordDuration:recordDuration];
}

- (void)purgeGPUCache {
    [self cleanCache];
}

- (void)setRecordProgressChangedHandler:(void (^)(double))recordProgressChangedHandler {
    [self.adapter setRecordProgressChangedHandler:recordProgressChangedHandler];
}

- (void (^)(double))recordProgressChangedHandler {
    return [self.adapter recordProgressChangedHandler];
}

- (void)setRecordDurationReachedHandler:(void (^)(void))recordDurationReachedHandler {
    [self.adapter setRecordDurationReachedHandler:recordDurationReachedHandler];
}

- (void (^)(void))recordDurationReachedHandler {
    return [self.adapter recordDurationReachedHandler];
}

- (void)setCompleteProgressUpdateHandler:(void (^)(double))completeProgressUpdateHandler {
    [self.adapter setCompleteProgressUpdateHandler:completeProgressUpdateHandler];
}

- (void (^)(double))completeProgressUpdateHandler {
    return [self.adapter completeProgressUpdateHandler];
}

- (void)setRecordSegmentsChangedHandler:(void (^)(NSArray *, NSArray *, BOOL))recordSegmentsChangedHandler {
    [self.adapter setRecordSegmentsChangedHandler:recordSegmentsChangedHandler];
}

- (void (^)(NSArray *, NSArray *, BOOL))recordSegmentsChangedHandler {
    return [self.adapter recordSegmentsChangedHandler];
}

- (NSTimeInterval)recordDuration {
    return [self.adapter recordDuration];
}

- (BOOL)hasDetectorBareness {
    return  [self.adapter hasDetectorBareness];
}

#pragma mark - background music
- (void)setBackgroundAudio:(AVAsset *)backgroundAudio {
   self.adapter.backgroundAudio = backgroundAudio;
}

- (AVAsset *)backgroundAudio {
    return self.adapter.backgroundAudio;
}

// ---
- (id)periodicTimeObserver {
    return self.adapter.periodicTimeObserver;
}

- (BOOL)stopMerge {
    return self.adapter.stopMerge;
}

- (BOOL)isFaceCaptured {
    return self.adapter.isFaceCaptured;
}
// ---

#pragma mark - record relates
- (BOOL)isRecording {
    return self.adapter.isRecording;
}

- (void)captureStillImage {
    self.adapter.captureStillImageWillHandler = self.captureStillImageWillHandler;
    self.adapter.captureStillImageHandler = self.captureStillImageHandler;
    [self.adapter takePhoto];
}

- (void)startRecording {
    [self.adapter startRecording];
}

- (void)stopVideoCaptureWithCompletionHandler:(void (^)(NSURL *videoFileURL, NSError *error))completionHandler {
    NSString *originalVideoFilePath = [MDRecordContext videoTmpPath];
    NSURL *finalUrl = [NSURL fileURLWithPath:originalVideoFilePath];
    
    [self.adapter stopVideoCaptureWithOutputURL:finalUrl completionHandler:completionHandler];
}

- (void)clearStashVideo {
    [self.adapter cleanStashFile];
}

- (void)pauseRecording {
    [self.adapter pauseRecording];
}

- (void)cancelRecording {
    [self.adapter cancelRecording];
}

- (void)resetRecorder {
    [self.adapter resetRecorder];
}

- (void)deleteLastSavedSegment {
    [self.adapter deleteLastSavedSegment];
}

- (NSTimeInterval)currentRecordingDuration {
    return self.adapter .currentRecordingDuration;
}

- (NSTimeInterval)currentRecordingPresentDuration {
    return self.adapter .currentRecordingPresentDuration;
}

- (NSInteger)savedSegmentCount {
    return [self.adapter savedSegmentCount];
}

- (BOOL)canStartRecording {
    return [self.adapter canStartRecording];
}

- (void)setOutputOrientation:(UIDeviceOrientation)outputOrientation {
    self.adapter.outputOrientation = outputOrientation;
}

- (UIDeviceOrientation)outputOrientation {
    return self.adapter.outputOrientation;
}

- (void)setFaceFetureHandler:(void (^)(CVPixelBufferRef))faceFetureHandler {
    self.adapter.faceFeatureHandler = faceFetureHandler;
}

- (void (^)(CVPixelBufferRef))faceFetureHandler {
    return self.adapter.faceFeatureHandler;
}

#pragma mark - process
- (void)configureFilterA:(MDRecordFilter *)filterA filterB:(MDRecordFilter *)filterB offset:(double)filterOffset {
    [self.adapter configFilterA:filterA configFilterB:filterB offset:filterOffset];
}

- (FDKDecoration *)makeDecorationWithBeautySettingsDict:(NSDictionary *)beautySettingsDict {
    MDBeautySettings *beautySettings = [[MDBeautySettings alloc] initWithDictionary:beautySettingsDict];
    return [beautySettings makeDecoration];
}

- (void)updateDecorationWithBeautySettingsDict:(NSDictionary *)beautySettingsDict decoration:(FDKDecoration *)decoration {
    MDBeautySettings *beautySettings = [[MDBeautySettings alloc] initWithDictionary:beautySettingsDict];
    [beautySettings updateDecorationBeautySetting:decoration];
}

- (void)setBeautyThinFace:(CGFloat)value {
    [self.adapter setBeautyThinFaceValue:value];
}

- (void)setBeautyBigEye:(CGFloat)value {
    [self.adapter setBeautyBigEyeValue:value];
}

- (void)setBeautySkinWhite:(CGFloat)value {
    [self.adapter setSkinWhitenValue:value];
}

- (void)setBeautySkinSmooth:(CGFloat)value {
    [self.adapter setSkinSmoothValue:value];
}

- (void)setBeautyLongLeg:(CGFloat)value {
    [self.adapter setBeautyLenghLegValue:value];
}

- (void)setBeautyThinBody:(CGFloat)value {
    [self.adapter setBeautyThinBodyValue:value];
}

- (void)addDecoration:(FDKDecoration *)decoration {
    
    if (decoration) {
        [self.adapter updateDecoration:decoration];
    
        [self configFaceTipManager:decoration.additionalInfo];
    }
}

- (void)configFaceTipManager:(NSDictionary *)additionalInfo {
    [self.faceTipManager stop];
    self.faceTipManager = [MDFaceTipManager managerWithDictionary:additionalInfo
                                                         position:self.cameraPosition
                                                       showTarget:self];
    
    [self.faceTipManager start];
}

- (void)configFaceTipManagerForEmptyDecoration {
    [self.faceTipManager stop];
    MDFaceTipItem *faceTipItem = [[MDFaceTipItem alloc] init];
    faceTipItem.content = @"露个脸吧";
    faceTipItem.shouldFaceTrack = YES;
    self.faceTipManager = [[MDFaceTipManager alloc] initWithFaceTipItem:faceTipItem position:self.cameraPosition showTarget:self];
    [self.faceTipManager start];
}

- (void)showFaceTipText:(NSString *)text {
    if (self.newFrameTipHandler) {
        self.newFrameTipHandler(text);
    }
}

- (void)faceTipDidFinishAllTask {
    self.faceTipManager = nil;
}

- (void)muteDecorationAudio:(BOOL)mute {
    [self.adapter adjustStikcerVolume:mute ? .0f : 1.0f];
}

- (void)removeAllDecoration {
    [self.adapter removeDecoration];
    
    [self.faceTipManager stop];
}

- (void)cleanCache {
    [self.adapter clean];
}

#pragma mark - camera control
- (void)startCapturing {
    [self.adapter startCapturing];
}

- (void)stopCapturing {
    [self.adapter stopCapturing];
}

- (void)pauseCapturing {
    [self.adapter pauseCapturing];
}

- (void)rotateCamera {
    [self.adapter switchCameraPosition];
    
    [self.faceTipManager input:MDFaceTipSignalCameraRotate];
}

- (void)focusCameraInPoint:(CGPoint)pointInCamera {
    [self.adapter focusCameraInPoint:pointInCamera];
}

- (BOOL)hasVideoInput {
    return [self.adapter hasVideoInput];
}

- (BOOL)hasFlash {
    return [self.adapter hasFlash];
}

- (NSArray *)supportFlashModes {
    return [self.adapter supportFlashModes];
}

- (void)setFlashMode:(MDRecordCaptureFlashMode)mode {
    self.adapter.flashMode = mode;
}

- (MDRecordCaptureFlashMode)flashMode {
    return self.adapter.flashMode;
}

- (AVCaptureDevicePosition)cameraPosition {
    return self.adapter.cameraPosition;
}

- (void)updateFaceTipWithAFaceFeature:(BOOL)isTracking {
    if (self.shouldContinue && _faceTipManager) {
        MDFaceTipSignal signal = isTracking ? MDFaceTipSignalFaceTrack:MDFaceTipSignalFaceNoTrack;
        
        if (self.currentSignal != signal) {
            __weak typeof(self) weakSelf = self;
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf.faceTipManager input:signal];
            });
        }
    }
}

- (void)runXESEngine {
    [self.adapter runXESEngineWithDecorationRootPath:[MDFaceDecorationFileHelper FaceDecorationBasePath]];
}

#pragma mark - audio pitch
- (void)handleSoundPitchWithAssert:(AVAsset *)videoAsset
                    andPitchNumber:(NSInteger)pitchNumber
                 completionHandler:(void (^) (NSURL *))completionHandler {
    [self.adapter handleSoundPitchWithAssert:videoAsset andPitchNumber:pitchNumber completionHandler:completionHandler];
}

//activateBarenessDetector
- (void)activateBarenessDetectorEnable:(BOOL)enable {
    [self.adapter activateBarenessDetectorEnable:enable];
}

#pragma mark - avcaptureSession 切 arkit
- (void)switchToCameraSourceType:(MDRecordCameraSourceType)cameraSourceType {
    [self.adapter switchToCameraSourceType:cameraSourceType];
}

- (MDRecordCameraSourceType)cameraSourceType {
    return self.adapter.cameraSourceType;
}

#pragma mark - AI美颜

- (void)downloadCXMakeupBundleIfNeeded {
    NSString *json = @"{\"metadata\":{\"title\":\"自然\",\"UUID\":\"A2EBA75C-3E7F-4CC8-835F-3002FA5C2383\",\"order\":50,\"overallSkinSmoothingAmount\":0.59999999999999998},\"faceAdjustments\":{\"chinLength\":0,\"jawWidth\":0,\"forehead\":0,\"noseLift\":0,\"noseWidth\":0,\"mouthSize\":0,\"eyeTilt\":0,\"eyeSize\":0.34999999999999998,\"noseSize\":0,\"jawShape\":0,\"noseRidgeWidth\":0,\"noseTipSize\":0,\"thinFace\":0.34999999999999998,\"lipThickness\":0,\"faceWidth\":0,\"eyeDistance\":0},\"makeup\":{\"layerConfigurations\":[{\"intensity\":0,\"layerIdentifier\":\"CXPreset.Blush.3\"}]},\"skinSmoothingSettings\":{\"amount\":0.59999999999999998,\"eyesAreaAmount\":0,\"nasolabialFoldsAreaAmount\":0},\"teethWhitenSettings\":{\"amount\":0}}";
    NSDictionary *dic = [NSJSONSerialization JSONObjectWithData:[json dataUsingEncoding:NSUTF8StringEncoding] options:NSJSONReadingAllowFragments error:nil];
    CXBeautyConfiguration *config  = [CXBeautyConfiguration beautyConfigurationFromJSONObject:dic error:nil];
    [self.adapter setBeautyConfiguration:config];
}

#pragma mark - 变速

- (void)setNextRecordSegmentSpeedVaryFactor:(CGFloat)factor {
    [self.adapter setNextRecordSegmentSpeedVaryFactor:factor];
}

- (CGFloat)nextRecordSegmentSpeedVaryFactor {
    return [self.adapter nextRecordSegmentSpeedVaryFactor];
}

- (void)speedVaryShouldAllow:(BOOL)isAllow {
    [self.adapter speedVaryShouldAllow:isAllow];
}

- (BOOL)hasPerSpeedEffect {
    return [self.adapter hasPerSpeedEffect];
}

@end
