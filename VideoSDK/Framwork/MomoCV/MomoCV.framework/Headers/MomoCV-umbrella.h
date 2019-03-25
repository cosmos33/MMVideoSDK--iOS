#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "MMFaceFeature.h"
#import "MMFaceDetector.h"
#import "MMFaceWarper.h"
#import "MMBodyWarper.h"
#import "MMFacialExpressionDetector.h"
#import "MMObjectDetector.h"
#import "MMObjectFeature.h"
#import "MMObjectTracker.h"
#import "MMBodyDetector.h"
#import "MMCVModelLoading.h"
#import "MMOpticalFlowMotionDetector.h"
#import "MMObjectDetectorTrackingHelper.h"
#import "MMImageQualityAnalyzer.h"
#import "MMCVDetectionOptions.h"
#import "MMImageSegmenter.h"
#import "MMSoundTracker.h"
#import "MMAudioClassifier.h"
#import "MMBarenessDetector.h"
#import "MMFaceRigDetector.h"
#import "MMCashDetector.h"
#import "MMFaceRecognizer.h"
#import "MMFaceAdjustment.h"
#import "MMFaceRegister.h"
#import "MMFaceScanner.h"
#import "MMCVResources.h"
#import "MMFaceCluster.h"
#import "MMFaceQuality.h"
#import "MMFaceQualityDetector.h"
#import "MMLipsSegmenter.h"
#import "MMDelaunayTriangulation.h"
#import "MMCoreMLBodyDetector.h"
#import "MMGenderDetector.h"
#import "MMOpenCVUtilities.h"
#import "MMAgeDetector.h"
#import "MMExpressionDetector.h"
#import "MMFaceGender.h"
#import "MMCVCGImageUtilities.h"
#import "MMHandFeature.h"
#import "MMHandGestureDetector.h"
#import "MMMangaFaceProcessing.h"
#import "MMBodyJoint.h"
#import "MMHandLandmarker.h"
#import "MMFaceAttractivenessAnalyzer.h"

FOUNDATION_EXPORT double MomoCVVersionNumber;
FOUNDATION_EXPORT const unsigned char MomoCVVersionString[];

