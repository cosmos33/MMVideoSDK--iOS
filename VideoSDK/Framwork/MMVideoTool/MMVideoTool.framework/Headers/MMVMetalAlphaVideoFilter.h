//
//  MMVMetalAlphaVideoFilter.h
//  MMVideoToolDemo
//
//  Created by 杨乃川 on 2018/5/28.
//  Copyright © 2018年 杨乃川. All rights reserved.
//

#import <Foundation/Foundation.h>

@import MetalPetal;
@interface MMVMetalAlphaVideoFilter : MTIUnaryImageRenderingFilter

@property (nonatomic, assign) float scaleFactor;

@end
