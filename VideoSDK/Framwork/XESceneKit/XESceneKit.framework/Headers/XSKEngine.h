//
// Created by momo783 on 02/08/2018.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN

@interface XSKEngine : NSObject

@property (nonatomic, strong, readonly) NSString  *resourcePath;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)shareInstance;

- (BOOL)configResourcePath:(NSString *)resourcePath;

- (BOOL)runEngine;

- (BOOL)isRunning;

- (void)updateRenderSize:(CGSize)renderSize;

- (void)render;

- (void)render:(NSString*)renderID;

- (void)endRunEngine;

- (void)enableClearColor:(BOOL)enable;

- (void)addSearchPath:(NSString *)relationSearchPatch;

@end

NS_ASSUME_NONNULL_END
