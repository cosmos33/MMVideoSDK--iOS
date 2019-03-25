//
//  MMAgeDetector.h
//  Pods
//
//  Created by Yu Ao on 31/03/2018.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>


NS_ASSUME_NONNULL_BEGIN

@class MMFaceFeature;

@interface MMFaceAge: NSObject <NSCopying>

@property (nonatomic, readonly) NSUInteger value;

@end

@interface MMAgeDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMFaceAge *)ageForFaceFeature:(MMFaceFeature *)faceFeature inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
