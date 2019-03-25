//
//  MDSpecialFilterLifeStyleProtocol.h
//  MomoChat
//
//  Created by sunfei on 2018/8/14.
//  Copyright © 2018 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MDSpecialFilterLifeStyleProtocol <NSObject>

- (void)willEnter;
- (void)didEnter;
- (void)willLeave;
- (void)didLeave;

@end
