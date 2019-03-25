//
//  XSKEngine+Lua.h
//  XESceneKit
//
//  Created by momo783 on 16/08/2018.
//

#import <XESceneKit/XSKEngine.h>

@interface XSKEngine (Lua)

- (void)setupLuaScriptEngine;

- (void)setupLuaSecretKey:(NSString*)secretKey;

- (void)execteScriptFile:(NSString *)scriptFile;

- (void)execteGameScriptFile:(NSString *)scriptFile;

@end
