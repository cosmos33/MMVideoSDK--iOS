//
//  MMOpenCVUtilities.h
//  MomoCV
//
//  Created by Yu Ao on 27/03/2018.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class MMFaceFeature;

NS_ASSUME_NONNULL_BEGIN

@interface MMOpenCVUtilities : NSObject

@end


@interface MMSkinDefectsRemovingOptions: NSObject

@property (nonatomic) int adaptiveThresholdBlockSize;

@property (nonatomic) double adaptiveThresholdC;

@property (nonatomic) double inpaintRadius;

@end

@interface MMSkinDefectsRemovingUtility: NSObject

+ (CGImageRef)imageByRemovingSkinDefectsInImage:(CGImageRef)image faceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures options:(MMSkinDefectsRemovingOptions *)options CF_RETURNS_NOT_RETAINED;

@end

NS_ASSUME_NONNULL_END
