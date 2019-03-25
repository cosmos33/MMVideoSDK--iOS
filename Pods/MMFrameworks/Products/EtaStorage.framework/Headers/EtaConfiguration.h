//
//  EtaConfiguration.h
//  Eta
//
//  Created by momo783 on 2016/11/10.
//  Copyright © 2016年 momo783. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MMFoundation/MMFoundation.h>

@class EtaModel;

NS_ASSUME_NONNULL_BEGIN

// asynchronous query callback
typedef void (^EtaCompletionBlock) (EtaModel * model);
typedef void (^EtaQueryCompletionBlock) (NSArray <EtaModel *> * models);

@interface EtaConfiguration : NSObject

@property (nonatomic, strong) NSString *tableNamePrefix;

/**
 *  Database version
 */
@property (nonatomic, assign) NSInteger version;

/**
 *  Clear time interval
 */
@property (nonatomic, assign) NSTimeInterval clearTimeInterval;

/**
 *  Support alert table column
 */
@property (nonatomic, assign, getter=canAlertTableColumn) BOOL alertTableColumn;

// Log switch
@property (nonatomic, assign, getter=isEnableLog) BOOL enableLog;

/**
 *  Namespace
 */
@property (readonly) NSArray  *allNameSpaces;
@property (readonly) NSString *defaultNameSpace;

@property (readonly) NSArray *allClasses;

/**
 *  The old version compatibility
 */
@property (readonly) MDThreadSafeDictionary <NSNumber*, Class> *enumMaps;


/**
 *  Classes with namespace
 */
- (void)registerClasses:(NSSet *)modelClasses;
- (void)registerClasses:(NSSet *)modelClasses forNameSpace:(NSString *)nameSpace;

/**
 *  Enum type with namespace
 */
- (NSSet *)classes;
- (NSSet *)classesForNameSpace:(NSString *)nameSpace;

/**
 *  If modelclass can be supported.
 */
- (BOOL)canStoreClass:(Class)modelClass;
- (BOOL)canStoreClass:(Class)modelClass forNameSpace:(NSString *)nameSpace;

/**
 *  The old enum type compatibility
 */
- (void)registerEnumMaps:(NSDictionary *)maps;

@end

NS_ASSUME_NONNULL_END
