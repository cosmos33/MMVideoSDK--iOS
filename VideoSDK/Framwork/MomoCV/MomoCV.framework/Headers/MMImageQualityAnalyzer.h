//
//  MMImageQualityAnalyzer.h
//  Pods
//
//  Created by YuAo on 11/04/2017.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMImageQualityAnalyzeResult : NSObject <NSCopying>

@property (nonatomic,readonly) float score;

- (instancetype)init NS_UNAVAILABLE;

@end

@interface MMImageQualityAnalyzer : NSObject

@property (nonatomic,copy,readonly) NSURL *alignmentModelURL;

@property (nonatomic,copy,readonly) NSURL *attributePredictionModelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (MMImageQualityAnalyzeResult *)analyzePixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
