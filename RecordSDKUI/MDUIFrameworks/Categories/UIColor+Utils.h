//
//  UIColor+Utils.h
//  Pods
//
//  Created by RecordSDK on 2016/9/27.
//
//

#import <UIKit/UIKit.h>

@interface UIColor (Utils)

+ (UIColor *)colorWithHexString: (NSString*)hex;//#aabbcc

//带alpha通道的十六进制串
+ (UIColor *)colorWithARGBHexString: (NSString*)hex;//#AARRGGBB

+ (UIColor *)colorWithRGBString: (NSString *)string;//@"255, 255, 255"
+ (UIColor *)colorWithRGBString:(NSString *)string defaultColor:(UIColor *)color;

@end
