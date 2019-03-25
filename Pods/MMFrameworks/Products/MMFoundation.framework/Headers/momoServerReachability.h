//
//  momoServerReachability.h
//  momoServerReachability
//  用于检测服务器链接状态，和当前网络情况
//  Created by xtra on 13-8-15.
//  Copyright (c) 2013年 immomo. All rights reserved.
//

#define KHOSTNAME @"www.apple.com"
#define MAXADDRS    32
extern char *if_names[MAXADDRS];
extern char *ip_names[MAXADDRS];
extern char *hw_addrs[MAXADDRS];
extern unsigned long ip_addrs[MAXADDRS];



#import <Foundation/Foundation.h>

typedef enum {
    MomoServerReachabilityStatus_NotReachable = 0, // 无链接
    MomoServerReachabilityStatus_ReachableViaWiFi, // 通过wifi链接
    MomoServerReachabilityStatus_ReachableViaWWAN  // 通过手机网络链接
}MomoServerReachabilityStatus;

@protocol momoServerReachabilityDelegate;
@interface momoServerReachability : NSObject 
{
    id<momoServerReachabilityDelegate> delegate;
    NSString *hostName;
    NSString *pingHostName;
}
@property (nonatomic, assign) id<momoServerReachabilityDelegate> delegate;
@property (nonatomic, retain) NSString *hostName;
@property (nonatomic, retain) NSString *pingHostName;
- (void)removeDelegate;

// reachability
- (void)checkHostReachable;
- (void)checkInternetReachable;
- (void)checkWifiReachable;
// ping
- (void)pingHost;
- (void)stopPing;
// ip
- (NSString *)getMyIPAddress;
// host parse
- (void)parseHost:(NSString *)apiHostName;
+ (NSString *)deviceIPAdress;
- (NSString *)getDNSServers;

@end

@protocol momoServerReachabilityDelegate <NSObject>
@required
- (void)didHostReachableStateChanged:(MomoServerReachabilityStatus)status;
- (void)didInternetReachableStateChanged:(MomoServerReachabilityStatus)status;
- (void)didWifiReachableStateChanged:(MomoServerReachabilityStatus)status;
- (void)pingRequestSent:(NSString *)log;
- (void)pingFailWithError:(NSString *)log;
- (void)pingResponseRecieved:(NSString *)log;
- (void)didReceiveUnexpectedPacket:(NSString *)log;
- (void)didHostAdressParsed:(NSString *)address host:(NSString *)host;
- (void)didHostAdressParseError:(NSError *)error host:(NSString *)host;
@end
