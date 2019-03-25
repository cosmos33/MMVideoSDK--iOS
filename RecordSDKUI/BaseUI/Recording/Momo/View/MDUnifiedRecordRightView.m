//
//  MDUnifiedRecordRightView.m
//  MDChat
//
//  Created by YZK on 2018/3/12.
//  Copyright © 2018年 sdk.com. All rights reserved.
//

#import "MDUnifiedRecordRightView.h"
#import "MDRecordGuideTipsManager.h"
#import "UIImage+MDUtility.h"
#import "MDRecordHeader.h"

NSString * const kMDRecordFilterOriginFilterIdentifier = @"原图";

const CGFloat kMDUnifiedRecordRightViewIconWidth = 50;
const CGFloat kMDUnifiedRecordRightViewRightMargin = 5.0;

static const CGFloat kMarginHeight = 15.0;

//static const NSInteger kFaceRedPointTag     = 10001;
//static const NSInteger kFilterRedPointTag   = 10002;
//static const NSInteger kMusicRedPointTag    = 10003;
//const NSInteger kThinBodyRedPointTag        = 10004;

@interface MDUnifiedRecordRightView ()

@property (nonatomic,strong) MDRecordGuideTipsManager   *tipsManager;

@property (nonatomic,strong) MDUnifiedRecordIconView *delayView;
@property (nonatomic,strong) MDUnifiedRecordIconView *speedView;
@property (nonatomic,strong) MDUnifiedRecordIconView *filterView;
@property (nonatomic,strong) MDUnifiedRecordIconView *faceDecorationView;
@property (nonatomic,strong) MDUnifiedRecordIconView *musicView;
@property (nonatomic,strong) MDUnifiedRecordIconView *thinView;

@property (nonatomic,strong) MDRecordFilter *currentFilter;

@property (nonatomic, assign) BOOL musicSelectedEnable;

@end


@implementation MDUnifiedRecordRightView

- (instancetype)initWithFrame:(CGRect)frame andGuideTipsManager:(MDRecordGuideTipsManager *)guideManager {
    self = [super initWithFrame:frame];
    if (self) {
        _tipsManager = guideManager;
        [self configUI];
    }
    return self;
}

- (void)configUI
{
    
    self.delayView = [self imageViewWithImageName:@"delayTime" title:@"定时" index:0 selStr:@"didTapDelayView"];
    
    self.musicView = [self imageViewWithImageName:@"bgMusic"
                                            title:@"配乐"
                                            index:1
                                           selStr:@"didTapMusicView"
                                  needScrollTitle:YES];
    
    self.filterView = [self imageViewWithImageName:@"filters"
                                             title:@"滤镜"
                                             index:2
                                            selStr:@"didTapFilterView"];
    
    self.thinView = [self imageViewWithImageName:@"beauty"
                                           title:@"美颜"
                                           index:3
                                          selStr:@"didTapThinView"];
    [self addSubview:self.thinView];

    self.faceDecorationView = [self imageViewWithImageName:@"changeFace"
                                                     title:@"变脸"
                                                     index:4
                                                    selStr:@"didTapFaceDecorationView"];
    
    self.speedView = [self imageViewWithImageName:@"speed" title:@"变速" index:5 selStr:@"didTapSpeedView"];
    
    [self addSubview:self.delayView];
    [self addSubview:self.speedView];
    [self addSubview:self.faceDecorationView];
    [self addSubview:self.filterView];
    [self addSubview:self.musicView];
    
    
    self.left = MDScreenWidth - kMDUnifiedRecordRightViewIconWidth - kMDUnifiedRecordRightViewRightMargin;
    self.size = CGSizeMake(kMDUnifiedRecordRightViewIconWidth, self.speedView.bottom);
    
//    if ([self.tipsManager canShowRedPointWithIdentifier:kRecordTipOfFilter]) {
//        UIImageView *redPointView = [self redPointViewLeft:(_filterView.width - 18) withTag:kFilterRedPointTag];
//        [_filterView addSubview:redPointView];
//    }
//
//    [self setFaceDecorationImageFromService];
//    if ([self.tipsManager canShowRedPointWithIdentifier:kRecordTipOfFace]) {
//        UIImageView *redPointView = [self redPointViewLeft:(_faceDecorationView.width - 18) withTag:kFaceRedPointTag];
//        [_faceDecorationView addSubview:redPointView];
//    }
    
//    if (canUseThin && [self.tipsManager canShowRedPointWithIdentifier:kRecordTipOfThin]) {
//        UIImageView *redPointView = [self redPointViewLeft:(_thinView.width - 18) withTag:kThinBodyRedPointTag];
//        [_thinView addSubview:redPointView];
//    }
//
//    NSString *musicID = [self.delegate musicIDFromOperation];
//    if (![musicID isNotEmpty] && [self.tipsManager canShowRedPointWithIdentifier:kRecordTipOfMusic]) {
//        UIImageView *redPointView = [self redPointViewLeft:(_musicView.width - 18) withTag:kMusicRedPointTag];
//        [_musicView addSubview:redPointView];
//    }
}

#pragma mark - public

//- (BOOL)hasRedPointOfFilterView {
//    UIView *redPointView = [self.filterView viewWithTag:kFilterRedPointTag];
//    return (redPointView != nil);
//}
//
//- (BOOL)hasRedPointOfFaceDecorationView {
//    UIView *redPointView = [self.faceDecorationView viewWithTag:kFaceRedPointTag];
//    return (redPointView != nil);
//}
//
//- (BOOL)hasRedPointOfMusicView {
//    UIView *redPointView = [self.musicView viewWithTag:kMusicRedPointTag];
//    return (redPointView != nil);
//}
//
//- (BOOL)hasRedPointOfThinView
//{
//    UIView *redPointView = [self.thinView viewWithTag:kThinBodyRedPointTag];
//    return (redPointView != nil);
//}

//- (CGRect)absoluteFrameOfFilterView
//{
//    CGRect absoluteFrame = CGRectZero;
//    absoluteFrame = [self convertRect:self.filterView.frame toView:[MDRecordContext appWindow]];
//    return absoluteFrame;
//}
//
//- (CGRect)absoluteFrameOfFaceDecorationView
//{
//    CGRect absoluteFrame = CGRectZero;
//    absoluteFrame = [self convertRect:self.faceDecorationView.frame toView:[MDRecordContext appWindow]];
//    return absoluteFrame;
//}
//
//- (CGRect)absoluteFrameOfMusicView
//{
//    CGRect absoluteFrame = CGRectZero;
//    absoluteFrame = [self convertRect:self.musicView.frame toView:[MDRecordContext appWindow]];
//    return absoluteFrame;
//}
//
//- (CGRect)absoluteFrameOfThinView
//{
//    CGRect absoluteFrame = CGRectZero;
//    absoluteFrame = [self convertRect:self.thinView.frame toView:[MDRecordContext appWindow]];
//    return absoluteFrame;
//}

//- (void)removeRedPointOfFilterView
//{
//    UIView *redPointView = [self.filterView viewWithTag:kFilterRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//    }
//}
//
//- (void)removeRedPointOfFaceDecorationView
//{
//    UIView *redPointView = [self.faceDecorationView viewWithTag:kFaceRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//    }
//}
//
//- (void)removeRedPointOfMusicView
//{
//    UIView *redPointView = [self.musicView viewWithTag:kMusicRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//    }
//}
//
//- (void)removeRedPointOfThinView
//{
//    UIView *redPointView = [self.thinView viewWithTag:kThinBodyRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//    }
//}

- (void)handleRotateWithTransform:(CGAffineTransform)transform
{
    self.delayView.transform = transform;
    self.speedView.transform = transform;
    self.filterView.transform = transform;
    self.faceDecorationView.transform = transform;
    self.musicView.transform = transform;
    self.thinView.transform = transform;
}

- (void)didShowFilter:(MDRecordFilter *)filter {
    if (self.currentFilter == filter) {
        return;
    }
    self.currentFilter = filter;
    
    if ([filter.identifier isEqualToString:kMDRecordFilterOriginFilterIdentifier]) {
        self.filterView.iconView.image = [UIImage imageNamed:@"moment_record_filter_icon"];
        self.filterView.titleLabel.text = @"滤镜";
    }else {
//        [self.filterView.iconView setImageWithURL:[NSURL URLWithString:filter.iconPath] effect:SDWebImageEffectCircle];
        [self.filterView.iconView sd_setImageWithURL:[NSURL URLWithString:filter.iconPath]];
        self.filterView.titleLabel.text = filter.name;
    }
}

- (MDRecordFilter *)currentShowFilter {
    return self.currentFilter;
}

- (void)didSelectMusicTitle:(NSString *)title {
    if ([title isNotEmpty]) {
        self.musicView.scrollLabel.text = title;
        self.musicView.iconView.image = [UIImage imageNamed:@"background_music_btn_selected"];
    }else {
        self.musicView.scrollLabel.text = @"配乐";
        self.musicView.iconView.image = [UIImage imageNamed:@"background_music_btn"];
    }
}

- (void)enableMusicSelected:(BOOL)enable {
    self.musicView.iconView.image = enable ? [UIImage imageNamed:@"bgMusic"] : [UIImage imageNamed:@"background_music_btn_noenable"];
    self.musicSelectedEnable = enable;
}

#pragma mark - event

- (void)didTapFaceDecorationView
{
//    UIView *redPointView = [self.faceDecorationView viewWithTag:kFaceRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//        [self.tipsManager redPointDidShowWithIdentifier:kRecordTipOfFace];
//    }
    
    if ([self.delegate respondsToSelector:@selector(didTapFaceDecorationView:)]) {
        [self.delegate didTapFaceDecorationView:self.faceDecorationView];
    }
}

- (void)didTapFilterView
{
//    UIView *redPointView = [self.filterView viewWithTag:kFilterRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//        [self.tipsManager redPointDidShowWithIdentifier:kRecordTipOfFilter];
//    }
    
    if ([self.delegate respondsToSelector:@selector(didTapFilterView:)]) {
        [self.delegate didTapFilterView:self.filterView];
    }
}

- (void)didTapThinView
{
//    UIView *redPointView = [self.thinView viewWithTag:kThinBodyRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//        [self.tipsManager redPointDidShowWithIdentifier:kRecordTipOfThin];
//    }
    
    if ([self.delegate respondsToSelector:@selector(didTapThinView:)]) {
        [self.delegate didTapThinView:self.thinView];
    }
}

- (void)didTapMusicView {
//    UIView *redPointView = [self.musicView viewWithTag:kMusicRedPointTag];
//    if (redPointView) {
//        [redPointView removeFromSuperview];
//        [self.tipsManager redPointDidShowWithIdentifier:kRecordTipOfMusic];
//    }
    
    if (!self.musicSelectedEnable) {
        return;
    }
    
    if ([self.delegate respondsToSelector:@selector(didTapMusicView:)]) {
        [self.delegate didTapMusicView:self.musicView];
    }
}

- (void)didTapSpeedView {
    if ([self.delegate respondsToSelector:@selector(didTapSpeedView:)]) {
        [self.delegate didTapSpeedView:self.speedView];
    }
}

- (void)didTapDelayView {
    if ([self.delegate respondsToSelector:@selector(didTapDelayView:)]) {
        [self.delegate didTapDelayView:self.delayView];
    }
}


#pragma mark - private

- (MDUnifiedRecordIconView *)imageViewWithImageName:(NSString *)imageName
                             title:(NSString *)title
                             index:(NSInteger)index
                            selStr:(NSString *)selStr
{
    return [self imageViewWithImageName:imageName title:title index:index selStr:selStr needScrollTitle:NO];
}

- (MDUnifiedRecordIconView *)imageViewWithImageName:(NSString *)imageName
                                              title:(NSString *)title
                                              index:(NSInteger)index
                                             selStr:(NSString *)selStr
                                    needScrollTitle:(BOOL)needScrollTitle {
    CGFloat top = (kMDUnifiedRecordRightViewIconWidth + kMarginHeight) * index;
    CGRect frame = CGRectMake(0, top, kMDUnifiedRecordRightViewIconWidth, kMDUnifiedRecordRightViewIconWidth);
    MDUnifiedRecordIconView *iconView = [[MDUnifiedRecordIconView alloc] initWithFrame:frame imageName:imageName title:title needScrollTitle:needScrollTitle target:self action:NSSelectorFromString(selStr)];
    return iconView;
}

- (void)setFaceDecorationImageFromService {
    NSString *imgUrl = [self faceIconUrlString];
    if ([imgUrl isNotEmpty]) {
        UIImage *image = _faceDecorationView.iconView.image;
        //服务器有下发icon时，使用下发icon
        __weak UIImageView *iconView = _faceDecorationView.iconView;
//        [iconView setImageWithURL:[NSURL URLWithString:imgUrl] effect:SDWebImageEffectDefault placeholderImage:image options:SDWebImageRetryFailed completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, NSURL *imageURL) {
//            iconView.image = image;
//        }];
        [iconView sd_setImageWithURL:[NSURL URLWithString:imgUrl] placeholderImage:image options:SDWebImageRetryFailed completed:^(UIImage *image, NSError *error, SDImageCacheType cacheType, NSURL *imageURL) {
            iconView.image = image;
        }];
    }
}

//查找当前可用的变脸入口图片
#warning sunfei
- (NSString *)faceIconUrlString {
    NSArray *iconInfoList = nil; //[[[MDContext currentUser] dbStateHoldProvider] faceGuideIconInfoList];
    
    __block NSString *faceIconUrl = nil;
    [iconInfoList enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        NSDictionary *iconInfo = obj;
        NSInteger startTime = [iconInfo integerForKey:@"start_time" defaultValue:0];
        NSInteger endTime = [iconInfo integerForKey:@"end_time" defaultValue:0];
        NSString *imageUrl = [iconInfo stringForKey:@"image_url" defaultValue:nil];
        
        NSTimeInterval interval = [[NSDate date] timeIntervalSince1970];
        if ([imageUrl isNotEmpty] && interval >= startTime && interval <= endTime) {
            faceIconUrl = imageUrl;
            *stop = YES;
        }
    }];
    
    return faceIconUrl;
}

//- (UIImageView *)redPointViewLeft:(CGFloat)left withTag:(NSUInteger)tag {
//    UIImageView *redPointView = [[UIImageView alloc] initWithFrame:CGRectMake(left, 0, 8, 8)];
//    redPointView.tag = tag;
//    UIImage *img = [UIImage imageWithColor:[UIColor redColor] finalSize:CGSizeMake(8, 8)];
//    img = [img clipCircle];
//    redPointView.image = img;
//    return redPointView;
//}



@end
