//
//  MDFastMP4Handler.m
//  MDChat
//
//  Created by YZK on 2019/1/9.
//  Copyright © 2019 sdk.com. All rights reserved.
//

#import "MDFastMP4Handler.h"
#import "MP4Fast.h"

@implementation MDFastMP4Handler

+ (int)MP4FastWithSrcMP4Path:(NSString *)pSrcMP4Path pDstMP4Path:(NSString *)pDstMP4Path {
    return MP4Fast([pSrcMP4Path UTF8String], [pDstMP4Path UTF8String]);
}

@end
