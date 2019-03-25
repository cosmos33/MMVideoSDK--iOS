//
//  NSData+Base64.h
//  MMFoundation
//
//  Created by momo783 on 2016/9/27.
//  Copyright © 2016年 momo783. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSData (Base64)

- (NSString *)base64Encoded;
- (NSData *)base64Decoded;

+ (NSData *)base64DataFromString:(NSString *)string;

@end

@interface NSString (Base64)

+ (NSString *)base64StringFromData:(NSData *)data length:(NSUInteger)length;

@end