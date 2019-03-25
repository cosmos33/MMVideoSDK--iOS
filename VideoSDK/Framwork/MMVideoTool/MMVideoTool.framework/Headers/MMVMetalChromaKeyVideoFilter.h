//
//  MMVMetalChromaKeyVideoFilter.h
//  MMVideoTool
//
//  Created by 杨乃川 on 2018/6/4.
//

#import <Foundation/Foundation.h>
@import MetalPetal;
@interface MMVMetalChromaKeyVideoFilter : MTIUnaryImageRenderingFilter
@property (nonatomic, assign) float threshold;
@property (nonatomic, assign) float smoothing;
@end
