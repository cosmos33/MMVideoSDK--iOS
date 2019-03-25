//
// Created by momo783 on 06/08/2018.
//

#import <Foundation/Foundation.h>
#import "CVEventProtocol.h"

@interface XSKEventDispatcher : NSObject

+ (void)updateFaceFeature:(id<CVFaceFeature>)faceFeature;

+ (void)updateFaceFeatures:(NSArray<id<CVFaceFeature>> *)faceFeatures;

+ (void)updateFaceFeatures:(NSArray<id<CVFaceFeature>> *)faceFeatures
         facialExpressions:(NSArray<NSArray<id<CVFacialExpression>> *> *)facialExpressions;

+ (void)updateExpressions:(NSArray<id<CVExpression>> *)expressions;

+ (void)updateBodyFeatures:(NSArray<id<CVBodyFeature>> *)bodyFeatures;

+ (void)updateHandFeatures:(NSArray<id<CVHandFeature>> *)handFeatures;

+ (void)updateObjectFeature:(NSArray<id<CVObjectFeature>> *)objectFeatures;

+ (void)lostAllCVFeatures;

@end


