//
//  MFSimpleDatabase.h
//  MomoFoundation
//
//  Created by Latermoon on 12-9-9.
//
//

#import <Foundation/Foundation.h>
#import <MFDB/FMDatabaseQueue.h>
#import <MFDB/MFDbCollection.h>
#import <MFDB/MFDbRow.h>

/*
 *精度补偿。当<%lf查询时，减去 ACCURACYCOMPENSATION，
 *当 >%lf查询时，加上 ACCURACYCOMPENSATION
 */
#define ACCURACYCOMPENSATION 0.0001

/**
 * 对FMDatabase进行封装，提供线程安全的数据库操作
 * 简化数据库操作，让数据库开发减少依赖SQL知识
 MFDbRow *row = [userColl findOne:@"momoid='100422' and remoteid='100428'"];
 MFDbList *list = [userColl find:@"momoid=100422" sort:@"loc_time" asc:YES];
 MFDbList *list = [userColl findAll];
 [userColl insert:userObj];
 [userColl update:userObj forKey:@"momoid" withValue:@"100422"];
 [userColl updateOrInsert:userObj forKey:@"momoid" withValue:@"100422"];
 [userColl deleteForKey:@"momoid" withValue:@"100422"];
 */
@interface MFSimpleDatabase : NSObject
{
    // 真正操作数据库的对象
    FMDatabaseQueue *innerDb;
    // 对collection:tableName方法进行缓存
    NSMutableDictionary *collCache;
    // 当前打开事务的计数器
    NSUInteger transactionCounter;
}

// 需要使用原生SQL语句时可以直接调用innerDb
@property (readonly) FMDatabaseQueue *innerDb;

#pragma mark - Init
+ (MFSimpleDatabase *)databaseWithPath:(NSString *)path;
- (MFSimpleDatabase *)initWithPath:(NSString *)path;

#pragma mark - Transaction
- (void)beginTransaction;
- (void)rollback;
- (void)commit;
- (BOOL)commitTransaction;

#pragma mark - Collection
// 获取数据库中的一个表
- (MFDbCollection *)collection:(NSString *)tableName;
- (NSError *)lastError;

#pragma mark - Query
- (MFDbList *)executeQuery:(NSString *)sql;
- (MFDbList *)executeQuery:(NSString *)sql withArgumentsInArray:(NSArray *)arguments;
- (MFDbList *)executeQuery:(NSString *)sql withParameterDictionary:(NSDictionary *)arguments;

- (MFDbList *)executeQuery:(NSString *)sql eliminateNull:(BOOL)flag;

#pragma mark - Fts3 offsets
- (MFDbList *)executeFtsRangeQuery:(NSString *)sql;

#pragma mark - Update
- (BOOL)executeUpdate:(NSString *)sql;
- (BOOL)executeUpdate:(NSString *)sql withArgumentsInArray:(NSArray *)arguments;
- (BOOL)executeUpdate:(NSString *)sql withParameterDictionary:(NSDictionary *)arguments;

- (BOOL)executeUpdates:(NSArray *)array;
- (BOOL)executeUpdates:(NSArray *)array outError:(NSError **)error;

#pragma mark - Index
- (BOOL)indexExist:(NSString *)indexName;
- (BOOL)tableExist:(NSString *)tableName;
- (BOOL)triggerExist:(NSString *)triggerName;

#pragma mark - Drop
- (BOOL)drop:(NSString *)aTableName;
- (BOOL)dropTrigger:(NSString *)aTriggerName;

#pragma mark - vague 模糊查找一个id
- (MFDbList *)getList:(NSString *)vagueName tableName:(NSString *)tableName findId:(NSString *)afindId;

- (BOOL)addColonmWith:(NSString *)name type:(NSString *)type to:(NSString *)tableName;
- (BOOL)addColonmsWith:(NSDictionary <NSString *, NSString *> *)colonms to:(NSString *)tableName;

//扩展一个返回错误值的方法，功能和这个方法一样：addColonmsWith:to:，为了不影响之前的逻辑，直接新加的
- (BOOL)addColumnsWithDictionary:(NSDictionary <NSString *, NSString *>*)dic tableName:(NSString *)name outError:(NSError **)error;
- (BOOL)addColumnsWithDictionary:(NSDictionary <NSString *, NSString *>*)dic tableName:(NSString *)name outError:(NSError **)error logBlock:(void(^)(NSString *, NSString *))logBlock;
@end
