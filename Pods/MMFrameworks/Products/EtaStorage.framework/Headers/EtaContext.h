//
//  EtaContext.h
//  MomoChat
//
//  Created by xu bing on 15/6/11.
//  Copyright (c) 2015年 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EtaConfiguration.h"

/**
 *  Asynchronous data model storage. 
 *  First, the data model is cached in memory,and then，to create an asynchronous task stored data to the DB.
 */

NS_ASSUME_NONNULL_BEGIN

@class MFSimpleDatabase;

@interface EtaContext : NSObject

+ (EtaContext *)shareInstance;

@property (readonly) EtaConfiguration *configuration;

/**
 Register configuration and switch DB.
 */
- (void)registerConfiguration:(EtaConfiguration *)configuration;

- (void)registerDBPath:(NSString *)dbPath;
- (void)switchDB:(MFSimpleDatabase *)database;


#pragma mark - query model
/**
 query all models with enum type.
 *
 *  @param modelType custom enum type bound to the Class
 *  @return query results
 */
- (NSArray *)allModels:(NSInteger)modelType;
/**
 query all models with enum type and block callback.
 */
- (void)allModels:(NSInteger)modelType completion:(EtaQueryCompletionBlock)block;


/**
 query a data model with identifier and enum type.
 *
 *  @param e_id model‘s unique identification
 *  @param modelType custom enum type bound to the Class
 *  @return query result
 */
- (id)modelWith:(NSString *)e_id andType:(NSInteger)modelType;
/**
 query a data model with identifier 、enum type and block callback.
 */
- (void)modelWith:(NSString *)e_id andType:(NSInteger)modelType completion:(EtaCompletionBlock)block;

/**
 query data model with identifiers and enum type.
 *
 *  @param e_ids model‘s unique identification array
 *  @param modelType custom enum type bound to the Class
 *  @return query results
 */
- (NSArray *)modelsWith:(NSArray *)e_ids andType:(NSInteger)modelType;
/**
 query data model with identifiers、enum type and block callback.
 */
- (void)modelsWith:(NSArray *)e_ids andType:(NSInteger)modelType completion:(EtaQueryCompletionBlock)block;


/**
 query data model with custom query conditions and enum type.
 */
- (NSArray *)modelsQuery:(NSString *)query withType:(NSInteger)modelType;
/**
 query data model with custom query conditions、enum type and block callback.
 */
- (void)modelsQuery:(NSString *)query withType:(NSInteger)modelType completion:(EtaQueryCompletionBlock)block;

/**
 query data model with custom query conditions、limit cout and enum type.
 */
- (NSArray *)modelsQuery:(NSString *)query limit:(int)count withType:(NSInteger)modelType;

/**
 query models count in database for enum type.
 */
- (NSInteger)modelsCount:(NSInteger)modelType;



#pragma mark - save model
/**
 save model asynchronously
 */
- (void)saveModel:(EtaModel *)model;

/**
 save model asynchronously
 */
- (void)saveModels:(NSArray <EtaModel *> *)models;



#pragma mark - remove model

/**
 Remove model data with identifier and enum type.
 */
- (void)removeModelWith:(NSString *)e_id andType:(NSInteger)modelType;

/**
 Remove model data with custom query condition and enum type.
 */
- (void)removeModelWithCondition:(NSString *)condition andType:(NSInteger)modelType;

/**
 Remove all model data with enum type.
 */
- (void)removeAllWithType:(NSInteger)modelType;

/**
 Remove the model data that time before specified date.
 */
- (void)removeAllBefore:(NSDate *)date andType:(NSInteger)modelType;

/**
 Remove the model data that time before specified date and query condition is custom.
 */
- (void)removeAllBefore:(NSDate *)date condition:(nullable NSString *)condition andType:(NSInteger)modelType;

#pragma mark - clear old data
/**
 *  clear old model data with enum type,just remove the data that time more than 30 days.
 */
- (BOOL)clearOldDatas:(NSInteger)modelType;

@end

NS_ASSUME_NONNULL_END
