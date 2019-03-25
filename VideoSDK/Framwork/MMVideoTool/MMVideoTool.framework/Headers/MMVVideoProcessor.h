//
//  MMVVideoProcessor.h
//  MMVideoTool
//
//  Created by 杨乃川 on 2018/6/4.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, MMVVideoProcessorResizingMode) {
    MMVVideoProcessorResizingModeScale,
    MMVVideoProcessorResizingModeAspect,
    MMVVideoProcessorResizingModeAspectFill
} ;

typedef NS_ENUM(NSUInteger, MMVVideoProcessorVideoType) {
    MMVVideoProcessorVideoTypeLeftAlpha,
    MMVVideoProcessorVideoTypeChroma
} ;


@interface MMVVideoProcessorOption : NSObject
@property (nonatomic, assign) MMVVideoProcessorVideoType videoType;
@property (nonatomic, assign) MMVVideoProcessorResizingMode resizingMode;
@end

@protocol MMVVideoProcessor<NSObject>

- (instancetype)initWithRenderTarget:(CGRect)renderedBounds option:(MMVVideoProcessorOption *)option;

- (void)processPixelBuffer:(CVPixelBufferRef)pixelBuffer;

- (void)clearContent;

@property (nonatomic, strong, readonly) UIView *renderingView;



@end

