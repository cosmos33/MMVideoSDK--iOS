//
//  MMBarenessDetector.h
//  MomoCV
//
//  Created by momo783 on 17/11/2017.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface MMBarenessDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (BOOL)detectVideoFrameBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (void)reset NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
