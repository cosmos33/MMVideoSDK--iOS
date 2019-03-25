//
//  MLSkinSmoothingMethod.h
//  MomoChat
//
//  Created by YuAo on 11/4/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

@import GPUImage;
@import FaceDecorationKitGPUImage;

NS_ASSUME_NONNULL_BEGIN

@protocol MLSkinSmoothingFilter <NSObject>

@property (nonatomic) CGFloat smoothingAmount;

- (void)applySkinColorThreshold:(nullable NSArray<NSNumber *> *)skinColorThreshold;

@end

@interface FDKSkinSmoothingFilter (MLSkinSmoothingFilter) <MLSkinSmoothingFilter>

@end

FOUNDATION_EXPORT BOOL MLGPUImageSkinSmoothingNewVersionEnabled(void);
FOUNDATION_EXPORT void MLGPUImageSkinSmoothingSetNewVersionEnabled(BOOL enabled);

@interface MLGPUImageSkinSmoothingMethod : NSObject

+ (GPUImageOutput<GPUImageInput,MLSkinSmoothingFilter> *)createSkinSmoothingFilter;

@end

NS_ASSUME_NONNULL_END
