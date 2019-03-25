//
//  MMLipsSegmenter.h
//  MomoCV
//
//  Created by Yu Ao on 15/03/2018.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>
#import "MMCVDetectionOptions.h"

NS_ASSUME_NONNULL_BEGIN

@class MMFaceFeature;

@interface MMLipsSegmentationResult: NSObject <NSCopying>

@property (nonatomic,readonly) NSData *data;

@property (nonatomic,readonly) size_t width;

@property (nonatomic,readonly) size_t height;

@property (nonatomic,readonly) CGRect sourceRegion;

@end

@interface MMLipsSegmenter : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (NSArray<MMLipsSegmentationResult *> *)lipsSegmentationResultsForFaceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures inPixelBuffer:(CVPixelBufferRef)pixelBuffer orientation:(MMCVImageOrientation)orientation;

- (void)reclaimResources;

@end

NS_ASSUME_NONNULL_END
