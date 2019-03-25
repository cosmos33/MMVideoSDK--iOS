//
//  MMBeautifulBodyWrapper.h
//  CocoaLumberjack
//
//  Created by Bruce on 2018/6/6.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
NS_ASSUME_NONNULL_BEGIN
@class MMBodyFeature;
@interface MMBodyWarperResult:NSObject<NSCopying>
@property (nonatomic,copy,readonly) NSData *sourceVerticesData;
@property (nonatomic,copy,readonly) NSData *destinationVerticesData;

@property (nonatomic,copy,readonly) NSArray<MMBodyFeature *> *bodyFeatures;

-(instancetype)initWithSourceVerticesData:(NSData *)sourceVerticesData destinationVerticesData:(NSData *)destinationVerticesData faceFeatures:(NSArray<MMBodyFeature *> *)faceFeatures;

@end
@interface MMBodyWarper : NSObject
@property (nonatomic) float bodyWith;
@property (nonatomic) float legLength;
@property (nonatomic) float upBodyScaleFactor;
@property (nonatomic) bool gradualSwitch;
- (MMBodyWarperResult *)wrapperResultWithFeatures:(NSArray<MMBodyFeature *> *)bodyFeatures frameSize:(CGSize)frameSize;
@end
NS_ASSUME_NONNULL_END
