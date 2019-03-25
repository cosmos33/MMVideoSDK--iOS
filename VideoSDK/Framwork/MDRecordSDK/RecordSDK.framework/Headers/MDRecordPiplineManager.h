//
//  MDPipLineManager.h
//  testGPU
//
//  Created by sunfei on 2018/8/1.
//  Copyright © 2018 MOMO. All rights reserved.
//

#import <GPUImage/GPUImage.h>
#import "MDSpecialFilterLifeStyleProtocol.h"

@class MDRecordPiplineItem;
//注意线程同步,都应该在GPUImage的线程中调用
@interface MDRecordPiplineManager : NSObject

@property (nonatomic, assign) BOOL reverse;
@property (nonatomic, strong, readonly) NSMutableArray<MDRecordPiplineItem *> *items;

- (instancetype)initWithDuraion:(CMTimeRange)duration;
- (void)insertRange:(CMTimeRange)range filter:(GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *)filter;
- (void)deleteLastFilter;
- (void)deleteAllFilter;

- (void)updateCurrentItemWithTime:(CMTime)time timeRange:(CMTimeRange)timeRange;
- (GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *)filterAtTime:(CMTime)time;

- (BOOL)hasFilter;

@end


@interface MDRecordPiplineItem : NSObject

- (instancetype)initWithFilter:(GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *)filter range:(CMTimeRange)range duraion:(CMTimeRange)duraion reverse:(BOOL)reverse;

@property (nonatomic, assign) CMTimeRange validRange;
@property (nonatomic, assign) BOOL reverse;
@property (nonatomic, readonly) GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *filter;

@property (nonatomic, readonly) NSValue *timeRangeValue;

- (BOOL)containTime:(CMTime)time;
- (BOOL)isEqualToTimeRange:(CMTimeRange)range;
- (BOOL)containTimeRange:(CMTimeRange)range;

@end
