//
//  MMSoundTracker.h
//  Pods
//
//  Created by momo783 on 31/08/2017.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMSoundTrackOptions : NSObject <NSCopying>

@property (readonly) NSInteger rate;
@property (readonly) NSInteger channels;
@property (readonly) NSArray <NSNumber *> *reserved;

- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWithRate:(NSInteger)rate channels:(NSInteger)channels reserved:(NSArray*)reserved NS_DESIGNATED_INITIALIZER;

@end

@interface MMSoundTrackResult : NSObject <NSCopying>

@property (readonly) NSInteger label;
@property (readonly) NSInteger energyRank;

- (instancetype)init NS_UNAVAILABLE;
- (nullable instancetype)initWith:(NSInteger)label energyRank:(NSInteger)energyRank NS_DESIGNATED_INITIALIZER;

@end



@interface MMSoundTracker : NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (BOOL)processSoundData:(NSData*)data segmentIndex:(NSInteger)segmentIndex options:(MMSoundTrackOptions*)options;

- (MMSoundTrackResult *)getTrackResult;

- (void)reset;

- (void)deleteSegment:(NSInteger)segmentIndex;


@end

NS_ASSUME_NONNULL_END
