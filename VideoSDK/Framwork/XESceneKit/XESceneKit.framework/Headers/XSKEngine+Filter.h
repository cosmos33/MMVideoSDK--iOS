//
// Created by momo783 on 02/08/2018.
//

#import <Foundation/Foundation.h>
#import "XSKEngine.h"

typedef void(^XSKMessageSendHandle)(NSString* message);

typedef NS_ENUM(NSInteger, XSKEngineCameraPosition) {
    XSKEngineCameraPositionFront,
    XSKEngineCameraPositionBack,
};

@interface XSKEngine (Filter)

- (void)rotateCamera:(XSKEngineCameraPosition)cameraPosition;

- (void)enableRecording:(BOOL)enabled; 


- (void)loadSceneWithRelatviePath:(NSString *)path sceneID:(NSString *)sceneID; //相对路径

- (void)loadSceneWithPath:(NSURL *)path sceneID:(NSString *)sceneID;    //绝对路径

- (void)unloadSceneWithSceneID:(NSString *)sceneID;

- (void)dispatchReceivedMessage:(NSString*)message;

- (void)registerMessageSendHandle:(XSKMessageSendHandle)sendHandle;

- (CGRect)getActorLocationFrame:(NSString *)actorName;

- (void)updateRelationLocationFrame:(CGRect)frame sceneId:(NSString*)sceneId;
- (void)updateRelationLocationFrame:(CGRect)frame sceneId:(NSString*)sceneId trackId:(NSUInteger)trackId;

- (void)tickTimeLineAndFrameSequence:(float)timeLine frameIndex:(NSUInteger)frameIndex sceneId:(NSString*)sceneId;

@end
