//
//  MLMetalPetalVideoProcessor.h
//  FaceDecorationKit
//
//  Created by 杨乃川 on 2018/1/3.
//

#import <Foundation/Foundation.h>
#import "MLVideoProcessor.h"
@import MetalPetal;
@import FaceDecorationKitMetalPetal;
@import FaceDecorationKitMomoCV;
@import NSTimerWeakTarget;
@import MLMediaFoundation;
@import MLFilterKitMetalPetal;
@import CXBeautyKit;

@interface MLMetalPetalVideoProcessor : NSObject<MLVideoProcessor>
@property (nonatomic, strong, readonly) MLAudioPrism <FDKAudioPrism>*audioPrism;
@property (nonatomic, assign) BOOL useDeepBeauty;
@property (nonatomic, copy) CXBeautyConfiguration *deepBeautyConfiguration;
@property (nonatomic, copy) NSArray <MLMetalPetalNativeViewItem *>*viewItems;
@end
