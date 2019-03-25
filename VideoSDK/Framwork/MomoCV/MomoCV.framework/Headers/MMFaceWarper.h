//
//  MMFaceWarper.h
//  Pods
//
//  Created by YuAo on 10/21/16.
//
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

@class MMFaceFeature, MMFaceAdjustmentOptions;

NS_ASSUME_NONNULL_BEGIN

#define MM_FACE_WARPER_DEPRECATED(reason) __attribute__((deprecated(reason))) NS_SWIFT_UNAVAILABLE(reason)

typedef NSString *MMFaceWarpType NS_EXTENSIBLE_STRING_ENUM;

FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeBeautyNatrual; //beauty_natrual
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeBeauty; //beauty
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeBeautyMultiFace;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeAwlFace;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeShortFace;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeBigHead;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeTinyFaceBigEye;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeSmallFaceBigEye;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeRectangleFaceSmallFeature;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypePearFaceSmallEyeBigMouth;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeRoundFace;
FOUNDATION_EXPORT MMFaceWarpType const MMFaceWarpTypeBigHead2;

@interface MMFaceWarpResult : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSData *sourceVerticesData;
@property (nonatomic,copy,readonly) NSData *destinationVerticesData;

@property (nonatomic,copy,readonly) NSArray<MMFaceFeature *> *faceFeatures;

@end

@interface MMFaceWarper : NSObject

@property (nonatomic,copy) MMFaceWarpType warpType;

/* beauty */
@property (nonatomic) float eyesEnhancementAmount;
@property (nonatomic) float faceThinningAmount;

/* warp */
@property (nonatomic) float warpAmount MM_FACE_WARPER_DEPRECATED("Replaced by `warpAmountAlpha` & `warpAmountBeta`");

@property (nonatomic) float warpAmountAlpha;
@property (nonatomic) float warpAmountBeta;

- (nullable MMFaceWarpResult *)warpResultWithFaceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures frameSize:(CGSize)frameSize;

- (nullable MMFaceWarpResult *)warpResultWithFaceFeatures:(NSArray<MMFaceFeature *> *)faceFeatures options:(MMFaceAdjustmentOptions *)options frameSize:(CGSize)frameSize;


@end

NS_ASSUME_NONNULL_END
