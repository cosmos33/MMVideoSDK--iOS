//
//  MMFaceAttractivenessAnalyzer.h
//  MomoCV
//
//  Created by Yu Ao on 2018/5/28.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

@class MMFaceFeature;

NS_ASSUME_NONNULL_BEGIN

@interface MMFaceAttractiveness: NSObject <NSCopying>

@property (nonatomic, readonly) float score;

@end

@interface MMFaceAttractivenessAnalyzer : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMFaceAttractiveness *)attractivenessForFaceFeature:(MMFaceFeature *)faceFeature inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
