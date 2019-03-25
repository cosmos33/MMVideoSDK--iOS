//
//  MMSoundClassifier.h
//  Pods
//
//  Created by Yu Ao on 11/10/2017.
//

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MMAudioType) {
    MMAudioTypeMusic,
    MMAudioTypeOthers
};

@interface MMAudioClassificationResult: NSObject <NSCopying>

@property (nonatomic,readonly) MMAudioType type;
@property (nonatomic,readonly) NSInteger energyRank;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface MMAudioClassifier: NSObject

@property (nonatomic,copy,readonly) NSURL *modelURL;

+ (BOOL)validateModelBundle:(NSBundle *)bundle;

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)new NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (BOOL)appendSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (BOOL)appendAudioData:(NSData *)data sampleRate:(double)sampleRate numberOfChannels:(NSUInteger)numberOfChannels;

@property (nonatomic,readonly,nullable) MMAudioClassificationResult *classificationResult;

- (void)reset;

@end

NS_ASSUME_NONNULL_END
