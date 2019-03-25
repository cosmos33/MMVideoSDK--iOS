//
//  BBGPUImageSlidingFilter.h
//  BiBi
//
//  Created by YuAo on 12/10/15.
//  Copyright © 2015 wemomo.com. All rights reserved.
//

#import <GPUImage/GPUImage.h>

@interface MDBBGPUImageSlidingFilter : GPUImageFilterGroup

@property (nonatomic) double offset; //-1...0...1

@property (nonatomic,strong) GPUImageOutput<GPUImageInput> *filterA;
@property (nonatomic,strong) GPUImageOutput<GPUImageInput> *filterB;

@end
