//
//  MMBodyJoint.h
//  MomoCV
//
//  Created by wuzhijia on 2018/7/18.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMBodyJoint : NSObject

@property (nonatomic,readonly) CGPoint location;

@property (nonatomic,readonly) float score;

- (instancetype)initWithLocation:(CGPoint)location score:(float)score;

@end

NS_ASSUME_NONNULL_END
