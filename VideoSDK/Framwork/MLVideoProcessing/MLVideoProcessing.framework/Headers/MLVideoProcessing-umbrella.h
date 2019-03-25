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

#import "MLBeautySettings.h"
#import "MLCameraSource.h"
#import "MLColorEnhancemnet.h"
#import "MLCVDetectorController.h"
#import "MLGPUImageDecorationManager.h"
#import "MLGPUImageLogarithmYFilter.h"
#import "MLGPUImageSkinSmoothingMethod.h"
#import "MLGPUImageVibranceFilter.h"
#import "MLGPUImageVideoProcessor.h"
#import "MLMediaSource.h"
#import "MLMetalPetalVideoProcessor.h"
#import "MLObjectTriggeredDecoration.h"
#import "MLVideoProcessor.h"
#import "MLVideoWatermarkProducer.h"
#import "MLVideoWatermarkView.h"

FOUNDATION_EXPORT double MLVideoProcessingVersionNumber;
FOUNDATION_EXPORT const unsigned char MLVideoProcessingVersionString[];

