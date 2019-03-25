//
// Created by HongjieFu on 2018/7/2.
//


#import <Foundation/Foundation.h>

typedef void(^XESBridgeThreadSafeQueue)(dispatch_block_t block);

@interface XESScriptBridge : NSObject

+ (void)regist:(id)handler
    forHandler:(NSString *)handlerName;

+ (void)unregist:(NSString *)handlerName;

+ (void)unregistAll;

+ (NSString *)callNative:(NSString *)handlerName
                  action:(NSString *)action
                 message:(NSString *)msg;

+ (void)callNativeAsync:(NSString *)handlerName
                 action:(NSString *)action
                message:(NSString *)msg
               callback:(void (^)(NSString *))callback;

+ (NSString *)callLua:(NSString *)handlerName
               action:(NSString *)action
              message:(NSString *)msg;

+ (void)callLuaAsync:(NSString *)handlerName
              action:(NSString *)action
             message:(NSString *)msg
            callback:(void (^)(NSString *))callback;

@end
