//
//  MDSpecialEffectsManager.h
//  MDChat
//
//  Created by YZK on 2018/8/8.
//  Copyright © 2018年 sdk.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MDSpecialEffectsModel.h"
#import <GPUImage/GPUImage.h>
#import <RecordSDK/MDSpecialFilterLifeStyleProtocol.h>

@interface MDRecordSpecialEffectsManager : NSObject

+ (GPUImageOutput<GPUImageInput,MDSpecialFilterLifeStyleProtocol> *)getFilterWithSpecialEffectsType:(MDRecordSpecialEffectsType)type;
+ (MDRecordSpecialEffectsType)getSpecialEffectsTypeWithFilter:(GPUImageOutput<GPUImageInput,MDSpecialFilterLifeStyleProtocol> *)filter;

+ (NSArray<MDSpecialEffectsModel*> *)getSpecialEffectsFilterModelArray;
+ (NSArray<MDSpecialEffectsModel*> *)getSpecialEffectsTimeModelArray;

@end
