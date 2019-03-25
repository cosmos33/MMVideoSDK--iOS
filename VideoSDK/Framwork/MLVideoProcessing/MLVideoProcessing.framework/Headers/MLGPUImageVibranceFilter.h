//
//  WLGPUImageVibranceFilter.h
//  Pods
//
//  Created by YuAo on 4/16/14.
//
//

@import GPUImage;

NS_ASSUME_NONNULL_BEGIN

@interface MLGPUImageVibranceFilter : GPUImageFilter

@property (nonatomic) CGFloat amount;

@property (nonatomic) BOOL avoidSaturatingSkinTones;

@end

NS_ASSUME_NONNULL_END
