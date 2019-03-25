//
//  EtaSyncContext.h
//  Eta
//
//  Created by momo783 on 2016/12/28.
//  Copyright © 2016年 momo783. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EtaConfiguration.h"

@class MFSimpleDatabase;

/**
 *  Synchronous data model storage，No Memory Cache.
 *  (Interface annotation reference EtaContext)
 */

NS_ASSUME_NONNULL_BEGIN

@interface EtaSyncContext : NSObject

@property (readonly) EtaConfiguration *configuration;

- (void)registerConfiguration:(EtaConfiguration *)configuration;

- (void)registerDBPath:(NSString *)dbPath;
- (void)switchDB:(MFSimpleDatabase *)database;

/** Query Model **/

- (NSArray *)allModels:(NSInteger)modelType;

- (id)modelWith:(NSString *)e_id andType:(NSInteger)modelType;

- (NSArray *)modelsWith:(NSArray *)e_ids andType:(NSInteger)modelType;

- (NSArray *)modelsQuery:(NSString *)query withType:(NSInteger)modelType;

- (NSArray *)modelsQuery:(NSString *)query limit:(int)count withType:(NSInteger)modelType;

- (NSInteger)modelsCount:(NSInteger)modelType;

/** Save Model  **/

- (void)saveModel:(EtaModel *)model;
- (void)saveModels:(NSArray <EtaModel *> *)models;

/** Remove Model */

- (void)removeModelWith:(NSString *)e_id andType:(NSInteger)modelType;

- (void)removeModelWithCondition:(NSString *)condition andType:(NSInteger)modelType;

- (void)removeAllWithType:(NSInteger)modelType;

- (void)removeAllBefore:(NSDate *)date andType:(NSInteger)modelType;

- (void)removeAllBefore:(NSDate *)date condition:(nullable NSString *)condition andType:(NSInteger)modelType;

/** Clear Old Data */

- (BOOL)clearOldDatas:(NSInteger)modelType;

@end

NS_ASSUME_NONNULL_END
