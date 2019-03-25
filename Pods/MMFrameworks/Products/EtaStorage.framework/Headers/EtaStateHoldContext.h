//
//  EtaStateHoldContext.h
//  Eta
//
//  Created by momo783 on 2016/11/27.
//  Copyright © 2016年 momo783. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class MFSimpleDatabase;
@interface EtaStateHoldContext : NSObject

+ (nullable EtaStateHoldContext *)sharedContext;

- (void)switchDB:(MFSimpleDatabase *)database ;


- (BOOL)containsObjectForKey:(nullable NSString *)key;

- (nullable id<NSCoding>)objectForKey:(nullable NSString *)key;
- (void)setObject:(nullable id<NSCoding>)object forKey:(nullable NSString *)key;

- (void)removeObjectForKey:(nullable NSString *)key;


- (BOOL)boolValueForKey:(nullable NSString *)key;
- (BOOL)boolValueForKey:(nullable NSString *)key defaultValue:(BOOL)value;

- (void)setBoolValue:(BOOL)value forKey:(nullable NSString *)key;


- (NSInteger)integerValueForKey:(nullable NSString *)key;
- (NSInteger)integerValueForKey:(nullable NSString *)key defaultValue:(NSInteger)value;

- (void)setIntegerValue:(NSInteger)value forKey:(nullable NSString *)key;


- (nullable NSNumber *)numberValueForKey:(nullable NSString *)key;
- (nullable NSNumber *)numberValueForKey:(nullable NSString *)key defaultValue:(nullable NSNumber *)value;

- (void)setNumberValue:(nullable NSNumber *)value forKey:(nullable NSString *)key;


- (nullable NSDate *)dateValueForKey:(nullable NSString *)key;
- (nullable NSDate *)dateValueForKey:(nullable NSString *)key defaultValue:(nullable NSDate *)value;

- (void)setDateValue:(nullable NSDate *)value forKey:(nullable NSString *)key;


- (nullable NSData *)dataValueForKey:(nullable NSString *)key;
- (nullable NSData *)dataValueForKey:(nullable NSString *)key defaultValue:(nullable NSData *)value;

- (void)setDataValue:(nullable NSData *)value forKey:(nullable NSString *)key;


- (nullable NSArray *)arrayValueForKey:(nullable NSString *)key;
- (nullable NSArray *)arrayValueForKey:(nullable NSString *)key defaultValue:(nullable NSArray *)value;

- (void)setArrayValue:(nullable NSArray *)value forKey:(nullable NSString *)key;

- (nullable NSDictionary *)dictionaryValueForKey:(nullable NSString *)key;
- (nullable NSDictionary *)dictionaryValueForKey:(nullable NSString *)key defaultValue:(nullable NSDictionary *)value;

- (void)setDictionaryValue:(nullable NSDictionary *)value forKey:(nullable NSString *)key;

@end

NS_ASSUME_NONNULL_END
