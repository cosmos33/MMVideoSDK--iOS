//
//  MLFaceDetectorController.h
//  MomoChat
//
//  Created by YuAo on 7/26/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

@import MomoCV;

NS_ASSUME_NONNULL_BEGIN
@interface MLCVDetectorController : NSObject

+ (instancetype)sharedController;

+ (nullable MMFaceDetector *)makeFaceDetector;

+ (nullable MMObjectDetector *)makeObjectDetector;

+ (nullable MMCoreMLBodyDetector *)makeBodyDetector NS_AVAILABLE(10_13, 11_0);

+ (nullable MMExpressionDetector *)makeExpressionDetector;

+ (nullable MMImageSegmenter *)makeImageSegmenter;

+ (nullable MMHandGestureDetector *)makeHandGestureDetector;

+ (BOOL)canCreateFaceDetector;

+ (BOOL)canCreateObjectDetector;

+ (BOOL)canCreateBodyDetector;

+ (BOOL)canCreateExpressionDetector;

+ (BOOL)canCreateImageSegmenter;

+ (BOOL)canCreateHandGestureDetector;
#if DEBUG
+ (BOOL)updateObjectDetectorModelWithURL:(NSURL *)url shouldValidate:(BOOL)shouldValidate; //file url
#endif


@property (nonatomic,readonly) BOOL shouldDetectFaces;

@property (nonatomic) BOOL faceBeautifierIsEnabled;
@property (nonatomic) BOOL hasFaceDecorations;
@property (nonatomic) BOOL faceBeautyCanUseLowFrequencyDetection;
@property (nonatomic) BOOL canUseLowFrequencyDetection;
@property (nonatomic) BOOL dokiEnable;
@property (nonatomic) BOOL shouldDetectBody;
@property (nonatomic) BOOL shouldDetectExpression;
@property (nonatomic) BOOL shouldSegmentImage;
@property (nonatomic) BOOL shouldDetectHandGesture;
@property (nonatomic) BOOL shouldDetectObject;
@property (nonatomic) NSUInteger handGestureType;

+ (void)installFaceDetector:(MMFaceDetector *)faceDetector;
+ (void)uninstallFaceDetector;

+ (void)installObjectDetector:(MMObjectDetector *)objectDetector;
+ (void)uninstallObjectDetector;

+ (void)installBodyDetector:(MMCoreMLBodyDetector *)bodyDetector NS_AVAILABLE(10_13, 11_0);
+ (void)uninstallBodyDetector;

+ (void)installExpressionDetector:(MMExpressionDetector *)expressionDetector;
+ (void)uninstallExpressionDetector;

+ (void)installImageSegmenter:(MMImageSegmenter *)imageSegmenter;
+ (void)uninstallImageSegmenter;

+ (void)installHandGestureDetector:(MMHandGestureDetector *)handGestureDetector;
+ (void)uninstallHandGestureDetector;

+ (void)uninstallAllDetectors;

@end

NS_ASSUME_NONNULL_END

