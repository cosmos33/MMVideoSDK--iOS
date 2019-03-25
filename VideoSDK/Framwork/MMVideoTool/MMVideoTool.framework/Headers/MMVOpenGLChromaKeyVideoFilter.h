//
//  MMVOpenGLChromaKeyVideoFilter.h
//  MMVideoTool
//
//  Created by 杨乃川 on 2018/6/4.
//

#import <Foundation/Foundation.h>
@import GPUImage;

@interface MMVOpenGLChromaKeyVideoFilter : GPUImageFilter
@property (nonatomic, assign) float threshold;
@property (nonatomic, assign) float smoothing;
//@property (nonatomic, assign) GPUVector3 colorToReplace;
@end
