//
//  NSDate+MFCateory.h
//  MomoChat
//
//  Created by lly on 13-2-16.
//  Copyright (c) 2013年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSDate (MFCateory)
//format是类似于@"YYYY-MM-DD HH:mm:ss"这样的字符串
-(NSString *)dateFormatString:(NSString *)format;

#pragma mark
-(int)day;
-(int)month;
-(int)year;
-(int)hour;
-(int)minute;
-(int)second;

- (NSDate *)beginningOfDay;
- (NSDate *)endOfDay;

- (NSDate *)beginningOfMonth;
- (NSDate *)endOfMonth;

@end
