//
//  EtaStoring.h
//  EtaContext
//
//  Created by momo783 on 2017/6/23.
//  Copyright © 2017年 wemomo. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol EtaStoring <NSObject, NSCoding>

@required
/**
 Database table primary key
 */
+ (NSString *)eta_key;

/**
 Model storage mapping
 *
 *  @return property attribute names
 */
+ (NSArray *)eta_dbStoreProperty;

/**
 Database table version
 */
+ (NSInteger)eta_dbVersion;

/**
 EtaStorage memory cache count limit
 */
+ (NSInteger)etaCountLimit;

/**
 After table created, call this interface.
 */
+ (void)eta_create:(NSString *)tableName;

/**
 After table dropped, call this interface to get clear list.
 *
 *  @return Dictionary, key is class name, value is EtadDropType.
 */
+ (NSDictionary *)eta_drop;

@end

typedef NS_ENUM(NSInteger, EtaDropType) {
    EtaDropTypeTable    = 0,
    EtaDropTypeClass    = 1,
};

NS_ASSUME_NONNULL_END

