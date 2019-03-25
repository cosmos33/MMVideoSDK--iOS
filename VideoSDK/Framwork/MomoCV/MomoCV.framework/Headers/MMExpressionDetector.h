//
//  MMExpressionDetector.h
//  MomoCV
//
//  Created by momo783 on 08/05/2018.
//

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger,MMExpressionEye) {
    MMExpressionEyeClose = 0,
    MMExpressionEyeOpen  = 1
};

typedef NS_ENUM(NSInteger,MMExpressionMouth) {
    MMExpressionMouthNotiong = 0,
    MMExpressionMouthDuzui   = 1,
    MMExpressionMouthSmile   = 2,
    MMExpressionMouthOpen    = 3
};

typedef NS_ENUM(NSInteger,MMExpressionHead) {
    MMExpressionHeadMiddle = 0,
    MMExpressionHeadLeft   = 1,
    MMExpressionHeadRight  = 2,
    MMExpressionHeadUp     = 3,
    MMExpressionHeadDown   = 4
};

typedef NS_ENUM(NSInteger,MMExpressionNeck) {
    MMExpressionNeckMiddle = 0,
    MMExpressionNeckLeft   = 1,
    MMExpressionNeckRight  = 2
};

@class MMFaceFeature;
@interface MMExpression : NSObject <NSCopying>

@property (nonatomic, readonly) MMExpressionEye leftEye;
@property (nonatomic, readonly) MMExpressionEye rightEye;

@property (nonatomic, readonly) MMExpressionHead head;
@property (nonatomic, readonly) MMExpressionNeck neck;

@property (nonatomic, readonly) MMExpressionMouth mouth;

- (NSString *)expression;

@end

@interface MMExpressionDetector : NSObject

@property (nonatomic,readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMExpression *)expressionForFaceFeature:(MMFaceFeature *)faceFeature inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (NSArray<MMExpression *>*)expressionsForFaceFeatures:(NSArray<MMFaceFeature *>*)faceFeatures inPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
