//
//  TraceRouter.h
//  TraceRouterTest
//
//  Created by xtra on 13-10-8.
//  Copyright (c) 2013年 immomo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "HostParse.h"
#import "Traveller.h"

@protocol TraceRouterDelegate <NSObject>
@required
- (void)TravellerNote:(NSString *)note;

@end

@class Traveller;
@interface TraceRouter : NSObject <HostParseDelegate,TravellerDelegate>
//@property (nonatomic, retain) HostParse *hostParse;
@property (nonatomic, retain) Traveller *traveller;
@property (nonatomic, assign) int ttl;
@property (nonatomic, assign) id<TraceRouterDelegate> delegate;

- (void)beginWith:(NSString *)url;

@end
