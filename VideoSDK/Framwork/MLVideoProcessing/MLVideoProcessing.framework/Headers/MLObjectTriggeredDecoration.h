//
//  MLObjectTriggeredDecoration.h
//  MomoChat
//
//  Created by YuAo on 11/16/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@class FDKDecoration;

@interface MLObjectTriggeredDecoration : NSObject <NSCopying>

@property (nonatomic,copy,readonly) NSString *objectTriggerType;

@property (nonatomic,readonly) NSTimeInterval duration;

@property (nonatomic,copy,readonly) FDKDecoration *decoration;

@property (nonatomic,copy,readonly) NSArray<NSNumber *> *triggerRegion;

- (instancetype)initWithObjectTriggerType:(NSString *)type
                            triggerRegion:(NSArray<NSNumber *> *)triggerRegion
                                 duration:(NSTimeInterval)duration
                               decoration:(FDKDecoration *)decoration;

@end
