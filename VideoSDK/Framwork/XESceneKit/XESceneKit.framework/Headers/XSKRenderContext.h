//
// Created by momo783 on 06/08/2018.
//

#import <Foundation/Foundation.h>

@interface XSKRenderContext : NSObject

+ (EAGLContext *)sharedRenderContext;

+ (dispatch_queue_t)sharedRenderQueue;

+ (void)syncRenderContextPerformBlock:(void (^)(void))block;

+ (void)asyncRenderContextPerformBlock:(void (^)(void))block;

@end

/**
 * ProcessingQueue
 */
void runSyncProcessingOnSceneRenderQueue(dispatch_block_t block);
void runAsyncProcessingOnSceneRenderQueue(dispatch_block_t block);

