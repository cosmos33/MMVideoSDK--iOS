//
//  MMFaceAdjustmentGeometryProvider.h
//  MomoCV
//
//  Created by Yu Ao on 30/01/2018.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class MMFaceFeature;

NS_ASSUME_NONNULL_BEGIN

@interface MMFaceAdjustments: NSObject <NSCopying>

@property (nonatomic) float faceWidth;
@property (nonatomic) float eyeSize;
@property (nonatomic) float lipThickness;
@property (nonatomic) float noseLift;

@property (nonatomic) float eyeTilt;
@property (nonatomic) float eyeDistance;

@property (nonatomic) float noseSize;
@property (nonatomic) float noseWidth;
@property (nonatomic) float noseRidgeWidth;
@property (nonatomic) float noseTipSize;

@property (nonatomic) float jawWidth;
@property (nonatomic) float jawShape;

@property (nonatomic) float chinLength;

@property (nonatomic) float forehead;

@property (nonatomic) float mouthSize;

@property (nonatomic) float thinFace;

@property (nonatomic) float eyebrowThickness;

+ (NSSet *)propertyKeys;

@property (nonatomic, readonly) BOOL isIdentity;

@end

@interface MMFaceAdjustmentInput: NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithFaceFeature:(MMFaceFeature *)faceFeature adjustments:(MMFaceAdjustments *)adjustments NS_DESIGNATED_INITIALIZER;

@end

@interface MMFaceAdjustmentOptions: NSObject <NSCopying>

@property (nonatomic) BOOL applyGradually;

@property (nonatomic) NSUInteger gradualFrames;

@property (nonatomic, class, readonly, strong) MMFaceAdjustmentOptions *defaultOptions;

@end

@interface MMFaceAdjustmentOutput: NSObject

@property (nonatomic, readonly) NSUInteger vertexCount;

@property (nonatomic, copy, readonly) NSData *verticsData;
@property (nonatomic, copy, readonly) NSData *textureCoordinatesData;

@property (nonatomic, copy, readonly) NSArray<MMFaceFeature *> *faceFeatures;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@property (nonatomic, readonly) CGRect safeArea;

@end

@interface MMFaceAdjustmentProcessor: NSObject

- (nullable MMFaceAdjustmentOutput *)outputForInputs:(NSArray<MMFaceAdjustmentInput *> *)inputs frameSize:(CGSize)frameSize;

- (nullable MMFaceAdjustmentOutput *)outputForInputs:(NSArray<MMFaceAdjustmentInput *> *)inputs options:(MMFaceAdjustmentOptions *)options frameSize:(CGSize)frameSize;

@end

NS_ASSUME_NONNULL_END
