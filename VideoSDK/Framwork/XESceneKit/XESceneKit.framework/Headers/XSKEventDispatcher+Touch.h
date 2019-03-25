//
//  XSKEventDispatcher+Touch.h
//  XEScene
//
//  Created by wuzhijia on 2018/8/18.
//

#import "XSKEventDispatcher.h"

@interface XSKEventDispatcher (Touchs)

+ (BOOL)hitTestTouch:(CGPoint)point withView:(UIView *)view;

+ (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

+ (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

+ (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

+ (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

@end
