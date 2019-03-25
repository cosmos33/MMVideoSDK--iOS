//
//  MFDb.h
//  MomoChat
//  由于batchupdate需要在业务层拼好sql语句，所以增加2个类方法负责生成sql语句
//  Created by xtra on 14/8/21.
//  Copyright (c) 2014年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MFDbHelper : NSObject

+ (NSString *)sqlFromReplaceFor:(NSDictionary *)dict with:(NSString *)tableName;
+ (NSString *)sqlFromUpdate:(NSString *)query row:(NSDictionary *)dictObj with:(NSString *)tableName;

@end
