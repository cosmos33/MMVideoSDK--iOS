//
//  MLMediaSource.h
//  Pods
//
//  Created by YuAo on 12/19/16.
//
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@protocol MLMediaSource;

@protocol MLMediaDataConsumer <NSObject>

@optional

- (void)mediaSource:(id<MLMediaSource>)source didOutputVideoSampleBuffer:(CMSampleBufferRef)sampleBuffer;
- (void)mediaSource:(id<MLMediaSource>)source didOutputAudioSampleBuffer:(CMSampleBufferRef)sampleBuffer;

- (void)mediaSource:(id<MLMediaSource>)source didRenderAudioData:(NSData*)sampleBuffer;

@end


@protocol MLMediaSource <NSObject>

- (void)addDataConsumer:(id<MLMediaDataConsumer>)dataConsumer;

- (void)removeDataConsumer:(id<MLMediaDataConsumer>)dataConsumer;

@end
