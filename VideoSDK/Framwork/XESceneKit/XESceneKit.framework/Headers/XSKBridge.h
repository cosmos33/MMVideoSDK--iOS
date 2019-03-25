//
//  XSKBridge.h
//  XEScene+Lua
//
//  Created by momo783 on 24/08/2018.
//

#import <Foundation/Foundation.h>

@interface XSKBridge : NSObject

+ (void)regist:(id)handler forHandler:(NSString *)handlerName;

+ (void)unregist:(NSString *)handlerName;

+ (void)unregistAll;

+ (NSString *)callLua:(NSString *)handlerName
               action:(NSString *)action
              message:(NSString *)msg;

+ (void)callLuaAsync:(NSString *)handlerName
              action:(NSString *)action
             message:(NSString *)msg
            callback:(void (^)(NSString *))callback;

@end
