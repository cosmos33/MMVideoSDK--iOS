//
//  MMHandFeature.h
//  MomoCV
//
//  Created by momo783 on 20/08/2018.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <GLKit/GLKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMHandGesture : NSObject <NSCopying>

@property (nonatomic,readonly) float score;

@property (nonatomic,copy,readonly) NSString *type;

@property (nonatomic,readonly)      CGRect bounds;

- (instancetype)init NS_UNAVAILABLE;

@end

@interface MMJoint : NSObject <NSCopying>

@property (nonatomic,readonly) float score;

@property (nonatomic,readonly) CGPoint location;

@property (nonatomic,readonly) GLKVector3 location3D;

@property (nonatomic,readonly) CGPoint location3DTo2D;

- (instancetype)init NS_UNAVAILABLE;

@end

@interface MMHandFeature : NSObject

@property (nonatomic,readonly) NSArray<MMJoint*> *landmarks;

@property (nonatomic,readonly) NSArray<NSNumber*> * params3D;

@property (nonatomic,readonly) NSArray<MMHandGesture*> *gestures;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
