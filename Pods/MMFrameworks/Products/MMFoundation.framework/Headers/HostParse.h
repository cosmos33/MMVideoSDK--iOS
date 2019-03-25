//
//  HostParse.h
//  MomoServerReachability
//
//  Created by xtra on 13-8-27.
//  Copyright (c) 2013年 immomo. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol HostParseDelegate;
@interface HostParse : NSObject
{
    NSString *hostName;
    NSData *hostAddress;
}
@property (nonatomic, retain) NSString *hostName;
@property (nonatomic, assign) id<HostParseDelegate> delegate;

- (void)start;
- (void)stop;

@end


@protocol HostParseDelegate <NSObject>
@optional
- (void) hostParse:(id)sender didFailWithError:(NSError *)error;
- (void) hostParse:(id)sender didParsedHostAddress:(NSData *)address;
@end