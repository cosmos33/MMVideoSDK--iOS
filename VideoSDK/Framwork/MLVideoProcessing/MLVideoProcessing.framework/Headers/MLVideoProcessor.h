//
//  MLVideoProcessor.h
//  MomoChat
//
//  Created by YuAo on 8/8/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import "MLObjectTriggeredDecoration.h"
@import MLMediaFoundation;
FOUNDATION_EXPORT BOOL MLSkinSmoothingNewVersionEnabled(void);
FOUNDATION_EXPORT void MLSkinSmoothingSetNewVersionEnabled(BOOL enabled);

OBJC_EXTERN  NSString *const MLSkinSmoothingMethodNewVersionEnabledKey;
OBJC_EXTERN  NSString *const MLSkinSmoothingMethodDidChangeNotification;

@class FDKDecoration,MLBeautySettings,MMFaceFeature,MMObjectFeature, MMBodyFeature,MLFilterDescriptor, MMFacialExpression, MMImageSegmentationResult, MLColorEnhancemnet;

@interface MLVideoProcessorOptions : NSObject

@end


@protocol MLVideoProcessor <NSObject>

@property (nonatomic,copy) MLFilterDescriptor *filterDescriptor;

@property (nonatomic,copy) MLBeautySettings *beautySettings;

@property (nonatomic,strong) MLColorEnhancemnet *colorEnhancement;

@property (nonatomic) CGRect cropRegion;

@property (nonatomic) CGFloat scale;

@property (nonatomic, strong, readonly)  MLAudioPrism *audioPrism;

@property (nonatomic, assign) BOOL beautyDisable;

@property (nonatomic, assign) float lookUpTableFilterIntensity;

- (nullable FDKDecoration *)decorationWithIdentifier:(NSString *)identifier;

- (void)addDecoration:(FDKDecoration *)decoration duration:(NSTimeInterval)duration positionType:(NSInteger)positionType;

- (void)addDecoration:(FDKDecoration *)decoration withIdentifier:(NSString *)identifier;

- (void)removeDecorationWithIdentifier:(NSString *)identifier;

@property (nonatomic,copy) NSArray<MLObjectTriggeredDecoration *> *objectTriggeredDecorations;

- (NSArray<NSString *> *)decorationIdentifiers;

- (void)processingCVPixelBuffer:(CVPixelBufferRef)pixelBuffer atTime:(CMTime)frameTime options:(MLVideoProcessorOptions *)options completion:(void (^)(CVPixelBufferRef resultPixelBuffer))completion;

- (void)setFaceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures objectFeatures:(NSArray<MMObjectFeature *> *)objectFeatures facialExpressions:(NSArray<MMFacialExpression *> *)facialExpressions imageSegmentationResult:(MMImageSegmentationResult *)imageSegmentationResult;

@end
