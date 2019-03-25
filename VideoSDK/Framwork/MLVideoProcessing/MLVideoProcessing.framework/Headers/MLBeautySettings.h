//
//  MLBeautySettings.h
//  MomoChat
//
//  Created by YuAo on 10/14/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MLBeautySettings : NSObject <NSCopying,NSSecureCoding>

@property (nonatomic) float skinSmoothingAmount;

@property (nonatomic) float eyesEnhancementAmount;

@property (nonatomic) float faceThinningAmount;

@property (nonatomic) float skinWhitenAmount;

@end

NS_ASSUME_NONNULL_END
