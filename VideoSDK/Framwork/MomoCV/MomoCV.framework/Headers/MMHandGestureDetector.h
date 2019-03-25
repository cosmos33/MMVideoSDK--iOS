//
// Created by momo783 on 20/08/2018.
//

#import <Foundation/Foundation.h>
#import "MMHandFeature.h"
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

@interface MMHandGestureOptions : NSObject

@property (nonatomic) MMCVImageOrientation orientation;

@property (nonatomic) NSUInteger handGestureType; // Default 0 : 0 : rain 1 : dance 2 : two hands

@property (nonatomic) NSUInteger detectSkipFrame; // Default 5

@end

@interface MMHandGestureDetector : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMHandFeature *)handFeaturesInPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (nullable MMHandFeature *)handFeaturesInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMHandGestureOptions*)options;

- (nullable MMHandFeature *)handFeaturesInPixelBuffer:(CVPixelBufferRef)pixelBuffer handFeature:(nullable MMHandFeature *)handFeature options:(MMHandGestureOptions*)options;

@end

NS_ASSUME_NONNULL_END
