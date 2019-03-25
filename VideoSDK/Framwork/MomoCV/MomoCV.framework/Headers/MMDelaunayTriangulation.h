//
//  MMDelaunayTriangulation.h
//  Pods
//
//  Created by Yu Ao on 17/03/2018.
//

#import <Foundation/Foundation.h>
#import <simd/simd.h>

NS_ASSUME_NONNULL_BEGIN

struct MMTriangulationTriangle {
    NSUInteger vertexIndexes[3];
};
typedef struct MMTriangulationTriangle MMTriangulationTriangle;

@interface MMDelaunayTriangulation : NSObject

@property (nonatomic, readonly) NSUInteger triangleCount;

@property (nonatomic, readonly) const MMTriangulationTriangle *triangles NS_RETURNS_INNER_POINTER;

- (MMTriangulationTriangle)triangleAtIndex:(NSUInteger)index;

- (instancetype)initWithPoints:(simd_float2 *)points count:(NSUInteger)count;

- (instancetype)initWithPoints:(NSArray<NSValue *> *)points;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
