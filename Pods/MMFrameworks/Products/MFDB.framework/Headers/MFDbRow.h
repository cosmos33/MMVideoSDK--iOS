//
//  MFDbRow.h
//  MomoFoundation
//
//  Created by Latermoon on 12-9-9.
//
//

#import <Foundation/Foundation.h>
#import <MMFoundation/MFDictionaryAccessor.h>
#import <MMFoundation/NSObject+MFDictionaryAdapter.h>

/**
 * 表示数据库中的一行，相比NSDictionary，MFDbRow主要的作用是数据类型转换
 * MFDbRow *row = [userColl findOne:@"momoid='100422'"];
 * NSString *momoid = [row stringForKey:@"momoid"];
 */
@interface MFDbRow : NSObject <MFDictionaryAccessor>
{
    NSDictionary *dataDict;
}

@property (readonly) NSDictionary *dataDict;

#pragma mark - Init
- (MFDbRow *)initWithDictionary:(NSDictionary *)aDataDict;

#pragma mark - MFDictionaryAccessor
- (id)objectForKey:(id)aKey;
- (void)setObject:(id)value forKey:(id)aKey;

//覆盖原生的dateForKey，因为NSDate存入数据库的时候会自动变成double型，所以取出时候是先取到NSNumber，需要转换成NSDate
- (NSDate *)dateForKey:(NSString *)aKey defaultValue:(NSDate *)value;

- (void)removeObjectForKey:(NSString *)aKey;

#pragma mark - Overide
- (NSString *)description;

@end

#pragma mark - Private
@interface MFDbRow (Private)

// 如果dataDict本身是NSMutableDictionary
- (NSMutableDictionary *)mutableDict;

@end
