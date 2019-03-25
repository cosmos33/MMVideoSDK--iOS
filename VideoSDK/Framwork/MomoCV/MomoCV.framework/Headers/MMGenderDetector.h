//
//  MMGenderDetector.h
//  Pods
//
//  Created by Yu Ao on 26/03/2018.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "MMFaceGender.h"

NS_ASSUME_NONNULL_BEGIN

@class MMFaceFeature;

@interface MMGenderDetectionResult: NSObject <NSCopying>

@property (nonatomic, readonly) MMFaceGender gender;

@end

@interface MMGenderDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (MMGenderDetectionResult *)genderForFaceFeature:(MMFaceFeature *)faceFeature inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
