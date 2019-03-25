//
//  MLGPUImageVideoProcessor.h
//  MomoChat
//
//  Created by YuAo on 8/8/16.
//  Copyright © 2016 wemomo.com. All rights reserved.
//

@import GPUImage;
#import "MLVideoProcessor.h"
#import "MLGPUImageDecorationManager.h"

@interface MLGPUImageVideoProcessor : NSObject <MLVideoProcessor>

@property (nonatomic,strong) MLGPUImageDecorationManager *decorationManager;

@end

FOUNDATION_EXPORT void MLGPUImageVideoProcessorSetForcesGLFinishBeforeOutput(BOOL forcesGLFinish);
