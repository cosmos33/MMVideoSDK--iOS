//
//  MMGestureFeature.h
//  Pods
//
//  Created by YuAo on 11/14/16.
//
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMObjectFeature : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSString *type;

@property (nonatomic,readonly)      CGRect bounds;

@property (nonatomic,readonly) float score;

- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
