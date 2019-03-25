//
//  MMObjectTracker.h
//  Pods
//
//  Created by YuAo on 1/19/17.
//
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMObjectTrackingResult : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic,readonly) BOOL targetLost;

@property (nonatomic,readonly) CGRect region;

@property (nonatomic,readonly) NSDictionary *dictionaryRepresentation;

- (instancetype)initWithDictionaryRepresentation:(NSDictionary *)dictionaryRepresentation;

@end


struct MMObjectTrackingLossThreadhold {
    int n;
    int N;
};
typedef struct MMObjectTrackingLossThreadhold MMObjectTrackingLossThreadhold;

@interface MMObjectTrackingOptions : NSObject <NSCopying>

@property (nonatomic) int orientations; //2

@property (nonatomic) BOOL enablesTrackingLossDetection; //default NO;

@property (nonatomic) float PSRThreshold; //default 13.5

@property (nonatomic) int PSRPeakDel; //default 1

@property (nonatomic) MMObjectTrackingLossThreadhold lossThreshold; //2/10

@property (nonatomic) BOOL enablesScaleEstimator; //default YES;

@end

@interface MMObjectTracker : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithOptions:(nullable MMObjectTrackingOptions *)options NS_DESIGNATED_INITIALIZER;

- (void)updateSourceRegion:(CGRect)region inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (MMObjectTrackingResult *)updateWithPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
