//
//  MDRecordPiplineFilterGroup.h
//  testGPU
//
//  Created by sunfei on 2018/8/1.
//  Copyright © 2018 MOMO. All rights reserved.
//

#import <GPUImage/GPUImage.h>
#import "MDSpecialFilterLifeStyleProtocol.h"
#import "MDRecordPiplineManager.h"

@interface MDRecordPiplineSpecificFilterGroup  : GPUImageFilterGroup

@property (nonatomic, assign) CMTimeRange timeRange;
@property (nonatomic, assign) BOOL reverse;
@property (nonatomic, strong, readonly) MDRecordPiplineManager *pipline;

- (void)addFilter:(GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *)newTarget timeRange:(CMTimeRange)range;
- (void)updateCurrentFilterWithTime:(CMTime)time timeRange:(CMTimeRange)timeRange;

- (void)deleteLastFilter;
- (void)deleteAllFilter;

@end

