//
//  MMCVModelLoading.h
//  Pods
//
//  Created by YuAo on 2/11/17.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const MMCVCoreMLModelPathExtension;

FOUNDATION_EXPORT NSString * const MMCVNoCompiledCoreMLModelPathExtension;

FOUNDATION_EXPORT NSString * const MMCVModelLoadingErrorDomain;

typedef NS_ENUM(NSUInteger, MMCVModelLoadingError) {
    MMCVModelLoadingErrorNone,
    MMCVModelLoadingErrorCannotLoadModel,
    MMCVModelLoadingErrorModelFileNotFound
};

NS_ASSUME_NONNULL_END
