//
//  MDSpecialEffectsManager.m
//  MDChat
//
//  Created by YZK on 2018/8/8.
//  Copyright © 2018年 sdk.com. All rights reserved.
//

#import "MDRecordSpecialEffectsManager.h"
#import "MDRecordHeader.h"
@import RecordSDK;

@implementation MDRecordSpecialEffectsManager

+ (GPUImageOutput<GPUImageInput,MDSpecialFilterLifeStyleProtocol> *)getFilterWithSpecialEffectsType:(MDRecordSpecialEffectsType)type
{
    switch (type) {
        case MDRecordSpecialEffectsTypeMirrImage:
        {
            MDRecordMirrImageFrameFilter *filter = [[MDRecordMirrImageFrameFilter alloc] init];
            return filter;
        }
            break;
        case MDRecordSpecialEffectsTypeRainWindow:
        {
            MDRecordRainWindowFilter *filter = [[MDRecordRainWindowFilter alloc] init];
            return filter;
        }
            break;
        case MDRecordSpecialEffectsTypeShake:
        {
            MDRecordShakeFilter *filter = [[MDRecordShakeFilter alloc] init];
            return filter;
        }
            break;
        case MDRecordSpecialEffectsTypeSoulOut:
        {
            MDRecordSoulOutFilter *filter = [[MDRecordSoulOutFilter alloc] init];
            return filter;
        }
            break;
        case MDRecordSpecialEffectsTypeTVArtifact:
        {
            MDRecordTVArtifactFilter *filter = [[MDRecordTVArtifactFilter alloc] init];
            return filter;
        }
            break;
        default:
            break;
    }
    return nil;
}

+ (MDRecordSpecialEffectsType)getSpecialEffectsTypeWithFilter:(GPUImageOutput<GPUImageInput,MDSpecialFilterLifeStyleProtocol> *)filter
{
    if ([filter isKindOfClass:[MDRecordMirrImageFrameFilter class]]) {
        return MDRecordSpecialEffectsTypeMirrImage;
    }
    else if ([filter isKindOfClass:[MDRecordRainWindowFilter class]]) {
        return MDRecordSpecialEffectsTypeRainWindow;
    }
    else if ([filter isKindOfClass:[MDRecordShakeFilter class]]) {
        return MDRecordSpecialEffectsTypeShake;
    }
    else if ([filter isKindOfClass:[MDRecordSoulOutFilter class]]) {
        return MDRecordSpecialEffectsTypeSoulOut;
    }
    else if ([filter isKindOfClass:[MDRecordTVArtifactFilter class]]) {
        return MDRecordSpecialEffectsTypeTVArtifact;
    }
    return nil;
}


+ (NSArray<MDSpecialEffectsModel*> *)getSpecialEffectsFilterModelArray {
    
    
    MDSpecialEffectsModel *shakeModel = [[MDSpecialEffectsModel alloc]init];
    shakeModel.effectsTitle = @"抖动";
    shakeModel.effectsImageName = @"";
    shakeModel.type = MDRecordSpecialEffectsTypeShake;
    shakeModel.bgColor = RGBACOLOR(71, 169, 238, 0.9);
    
    MDSpecialEffectsModel *soulOutModel = [[MDSpecialEffectsModel alloc]init];
    soulOutModel.effectsTitle = @"灵魂出窍";
    soulOutModel.effectsImageName = @"";
    soulOutModel.type = MDRecordSpecialEffectsTypeSoulOut;
    soulOutModel.bgColor = RGBACOLOR(243, 118, 138, 0.9);
    
    MDSpecialEffectsModel *tvModel = [[MDSpecialEffectsModel alloc]init];
    tvModel.effectsTitle = @"故障";
    tvModel.effectsImageName = @"";
    tvModel.type = MDRecordSpecialEffectsTypeTVArtifact;
    tvModel.bgColor = RGBACOLOR(71, 71 ,71, 0.9);
    
    MDSpecialEffectsModel *mirrModel = [[MDSpecialEffectsModel alloc]init];
    mirrModel.effectsTitle = @"四格子";
    mirrModel.effectsImageName = @"";
    mirrModel.type = MDRecordSpecialEffectsTypeMirrImage;
    mirrModel.bgColor = RGBACOLOR(107,240,226, 0.9);
    
    MDSpecialEffectsModel *rainModel = [[MDSpecialEffectsModel alloc]init];
    rainModel.effectsTitle = @"雨窗";
    rainModel.effectsImageName = @"";
    rainModel.type = MDRecordSpecialEffectsTypeRainWindow;
    rainModel.bgColor = RGBACOLOR(252, 238, 125, 0.9);
    
   
    NSMutableArray *marr = [NSMutableArray array];
    [marr addObjectSafe:shakeModel];
    [marr addObjectSafe:soulOutModel];
    [marr addObjectSafe:tvModel];
    [marr addObjectSafe:rainModel];
    [marr addObjectSafe:mirrModel];

    return marr;
}


+ (NSArray<MDSpecialEffectsModel*> *)getSpecialEffectsTimeModelArray {
    MDSpecialEffectsModel *noneModel = [[MDSpecialEffectsModel alloc]init];
    noneModel.effectsTitle = @"无";
    noneModel.effectsImageName = @"";
    noneModel.type = MDRecordSpecialEffectsTypeTimeNone;
    noneModel.isSelect = YES;
    
    MDSpecialEffectsModel *slowModel = [[MDSpecialEffectsModel alloc]init];
    slowModel.effectsTitle = @"慢动作";
    slowModel.effectsImageName = @"";
    slowModel.type = MDRecordSpecialEffectsTypeSlowMotion;
    slowModel.isSelect = NO;
    
    MDSpecialEffectsModel *quickModel = [[MDSpecialEffectsModel alloc]init];
    quickModel.effectsTitle = @"快动作";
    quickModel.effectsImageName = @"";
    quickModel.type = MDRecordSpecialEffectsTypeQuickMotion;
    quickModel.isSelect = NO;
    
    MDSpecialEffectsModel *repeatModel = [[MDSpecialEffectsModel alloc]init];
    repeatModel.effectsTitle = @"反复";
    repeatModel.effectsImageName = @"";
    repeatModel.type = MDRecordSpecialEffectsTypeRepeat;
    repeatModel.bgColor = RGBACOLOR(127, 255, 212, 0.3);
    repeatModel.isSelect = NO;
    
    
    MDSpecialEffectsModel *reverseModel = [[MDSpecialEffectsModel alloc]init];
    reverseModel.effectsTitle = @"倒放";
    reverseModel.effectsImageName = @"";
    reverseModel.type = MDRecordSpecialEffectsTypeReverse;
    reverseModel.bgColor = RGBACOLOR(71,169,238, 0.8);
    reverseModel.isSelect = NO;

    NSMutableArray *marr = [NSMutableArray array];
    [marr addObjectSafe:noneModel];
    [marr addObjectSafe:slowModel];
    [marr addObjectSafe:quickModel];
    [marr addObjectSafe:repeatModel];
    [marr addObjectSafe:reverseModel];

    return marr;
}



@end
