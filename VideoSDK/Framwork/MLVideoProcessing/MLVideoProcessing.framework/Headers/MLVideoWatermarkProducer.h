//
//  MLVideoWatermarkProducer.h
//  MomoChat
//
//  Created by YuAo on 11/10/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//
#import "MLVideoProcessor.h"

@interface MLVideoWatermarkProducer : NSObject

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithVideoProcessor:(id<MLVideoProcessor>)videoProcessor;

@property (nonatomic,weak,readonly) id<MLVideoProcessor> videoProcessor;

@end
