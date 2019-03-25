//
//  MMFacialExpressionDetector.h
//  Pods
//
//  Created by YuAo on 9/7/16.
//
//

#import <Foundation/Foundation.h>

#define MM_FACIAL_EXPRESSION_DEPRECATED(reason) __attribute__((deprecated(reason))) NS_SWIFT_UNAVAILABLE(reason)

NS_ASSUME_NONNULL_BEGIN

@class MMFaceFeature;

typedef NS_ENUM(NSUInteger, MMFacialExpressionType) {
    MMFacialExpressionTypeNormal = 0,
    
    MMFacialExpressionTypeMouthOpening = 1 << 0,
    MMFacialExpressionTypeMouthOpen = 1 << 1,
    
    MMFacialExpressionTypeLeftEyeOpen = 1 << 2,
    MMFacialExpressionTypeLeftEyeClosing = 1 << 3,
    MMFacialExpressionTypeLeftEyeBlink = 1 << 4,
    
    MMFacialExpressionTypeRightEyeOpen = 1 << 5,
    MMFacialExpressionTypeRightEyeClosing = 1 << 6,
    MMFacialExpressionTypeRightEyeBlink = 1 << 7,
    
    MMFacialExpressionTypeEyeBlink = 1 << 8,
    
    MMFacialExpressionTypeSmile = 1 << 9,
    MMFacialExpressionTypeDuckFace = 1 << 10,
    
    MMFacialExpressionTypeNod = 1 << 11,
};

typedef NS_OPTIONS(NSUInteger, MMFacialExpressionState) {
    MMFacialExpressionStateNormal MM_FACIAL_EXPRESSION_DEPRECATED("Replaced by MMFacialExpressionTypeNormal") = MMFacialExpressionTypeNormal,
    MMFacialExpressionStateMouthOpen MM_FACIAL_EXPRESSION_DEPRECATED("Replaced by MMFacialExpressionTypeMouthOpen") = MMFacialExpressionTypeMouthOpening
};

@interface MMFacialExpression : NSObject <NSCopying>

@property (nonatomic,readonly) MMFacialExpressionType type;

@property (nonatomic,readonly) float amount;

@end

FOUNDATION_EXPORT MMFacialExpression * _Nullable MMFacialExpressionGetExpressionOfTypeFromExpressions(MMFacialExpressionType type, NSArray<MMFacialExpression *> *expressions);
FOUNDATION_EXPORT MMFacialExpressionType MMFacialExpressionGetUnifiedExpressionFromExpressions(NSArray<MMFacialExpression *> *expressions);

@interface MMFacialExpressionDetector : NSObject

@property (nonatomic,readonly) MMFacialExpressionType state MM_FACIAL_EXPRESSION_DEPRECATED("Replaced by `expressions`.");

@property (nonatomic,copy,readonly) NSArray<MMFacialExpression *> *expressions;

- (NSArray<MMFacialExpression *> *)updateWithFaceFeature:(nullable MMFaceFeature *)faceFeature;

- (void)reset;

@end

NS_ASSUME_NONNULL_END
