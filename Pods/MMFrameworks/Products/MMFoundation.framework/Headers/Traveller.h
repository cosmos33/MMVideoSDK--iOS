//
//  Traveller.h
//  TraceRouterTest
//
//  Created by xtra on 13-10-9.
//  Copyright (c) 2013年 immomo. All rights reserved.
//

#import <Foundation/Foundation.h>

#if TARGET_OS_EMBEDDED || TARGET_IPHONE_SIMULATOR
#import <CFNetwork/CFNetwork.h>
#else
#import <CoreServices/CoreServices.h>
#endif

#include <AssertMacros.h>
#include "SimplePing.h"

// ICMP type and code combinations:

check_compile_time(sizeof(ICMPHeader) == 8);
check_compile_time(offsetof(ICMPHeader, type) == 0);
check_compile_time(offsetof(ICMPHeader, code) == 1);
check_compile_time(offsetof(ICMPHeader, checksum) == 2);
check_compile_time(offsetof(ICMPHeader, identifier) == 4);
check_compile_time(offsetof(ICMPHeader, sequenceNumber) == 6);

check_compile_time(sizeof(IPHeader) == 20);
check_compile_time(offsetof(IPHeader, versionAndHeaderLength) == 0);
check_compile_time(offsetof(IPHeader, differentiatedServices) == 1);
check_compile_time(offsetof(IPHeader, totalLength) == 2);
check_compile_time(offsetof(IPHeader, identification) == 4);
check_compile_time(offsetof(IPHeader, flagsAndFragmentOffset) == 6);
check_compile_time(offsetof(IPHeader, timeToLive) == 8);
check_compile_time(offsetof(IPHeader, protocol) == 9);
check_compile_time(offsetof(IPHeader, headerChecksum) == 10);
check_compile_time(offsetof(IPHeader, sourceAddress) == 12);
check_compile_time(offsetof(IPHeader, destinationAddress) == 16);


@protocol TravellerDelegate;
@interface Traveller : NSObject
@property (nonatomic, copy)    NSData                      *hostAddress;
@property (nonatomic, assign)               int                         ttl;
@property (nonatomic, assign)               id<TravellerDelegate>       delegate;
@property (nonatomic, assign, readonly )    uint16_t                    identifier;
@property (nonatomic, assign, readonly )    uint16_t                    nextSequenceNumber;
@property (nonatomic, assign) int ttlMax;

- (void)startWithHostAddress;
- (void)reset;
- (void)sendPingWithData:(NSData *)data;


@end

@protocol TravellerDelegate <NSObject>
@optional

- (void)Traveller:(Traveller *)pinger didStartWithAddress:(NSData *)address;
// Called after the SimplePing has successfully started up.  After this callback, you
// can start sending pings via -sendPingWithData:

- (void)Traveller:(Traveller *)pinger didFailWithError:(NSError *)error;
// If this is called, the SimplePing object has failed.  By the time this callback is
// called, the object has stopped (that is, you don't need to call -stop yourself).

// IMPORTANT: On the send side the packet does not include an IP header.
// On the receive side, it does.  In that case, use +[SimplePing icmpInPacket:]
// to find the ICMP header within the packet.

- (void)Traveller:(Traveller *)pinger didSendPacket:(NSData *)packet;
// Called whenever the SimplePing object has successfully sent a ping packet.

- (void)Traveller:(Traveller *)pinger didFailToSendPacket:(NSData *)packet error:(NSError *)error;
// Called whenever the SimplePing object tries and fails to send a ping packet.

- (void)Traveller:(Traveller *)pinger didReceiveResponsePacket:(NSData *)packet;
// Called whenever the SimplePing object receives an ICMP packet that looks like
// a response to one of our pings (that is, has a valid ICMP checksum, has
// an identifier that matches our identifier, and has a sequence number in
// the range of sequence numbers that we've sent out).

- (void)Traveller:(Traveller *)pinger didReceiveUnexpectedPacket:(NSData *)packet;
// Called whenever the SimplePing object receives an ICMP packet that does not
// look like a response to one of our pings.

@end



