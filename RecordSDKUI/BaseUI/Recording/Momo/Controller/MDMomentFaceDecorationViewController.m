//
//  MDMomentFaceDecorationController.m
//  MDChat
//
//  Created by wangxuan on 16/8/19.
//  Copyright © 2016年 sdk.com. All rights reserved.
//

#import "MDMomentFaceDecorationViewController.h"
#import "MDFaceDecorationItem.h"
//#import "MDFaceDecorationView.h"
#import "MDFaceDecorationPageView.h"
#import "MDPublicSwiftHeader.h"

static const NSString *kMomentFaceDecorationCell = @"MDMomentFaceDecorationCell";

#define kFaceDecorationViewH (250 + HOME_INDICATOR_HEIGHT)

@interface MDMomentFaceDecorationViewController ()
<UIGestureRecognizerDelegate,
NewFaceDecorationViewDelegate>

//@property (nonatomic, strong) MDFaceDecorationView        *decorationView;
@property (nonatomic, strong) UIVisualEffectView          *effectView;
@property (nonatomic, strong) UIView                      *contentView;
@property (nonatomic, strong) NewFaceDecorationView *newDecorationView;

@end

@implementation MDMomentFaceDecorationViewController

#pragma mark - life cycle
- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.hidden = YES;
    self.view.backgroundColor = [UIColor clearColor];
    self.view.frame = CGRectMake(0, MDScreenHeight - kFaceDecorationViewH , MDScreenWidth, kFaceDecorationViewH);
    [self.view addSubview:self.contentView];
    [self.contentView addSubview:self.effectView];
//    [self.contentView addSubview:self.decorationView];
    [self.contentView addSubview:self.newDecorationView];

    //dataHandle刷新通知
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadCollectionData:) name:MDFaceDecorationDrawerUpdateNotiName object:nil];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)setDataHandle:(MDFaceDecorationDataHandle *)dataHandle {
    _dataHandle = dataHandle;
    //变脸分类数据源
//    NSArray *classArray = [dataHandle getDrawerClassDataArray];
//    [self.decorationView updateSelectedViewItems:classArray];
    //变脸item数据源
//    NSArray *itemsArray = [dataHandle getDrawerDataArray];
//    [self.decorationView updatePageItems:itemsArray];
    
    NSArray<MDFaceDecorationItem *> *itemsArray = [dataHandle getDrawerDataArray][1];
    [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[0].resourcePath isNotEmpty] type:CellTypeGesture];
    [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[1].resourcePath isNotEmpty] type:CellTypeExpression];
    [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[2].resourcePath isNotEmpty] type:CellTypeEffect3D];
    [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[3].resourcePath isNotEmpty] type:CellTypeSegment];
}

- (void)setSelectedClassWithIdentifier:(NSString *)identifer {
//    [self.decorationView setSelectedClassWithIdentifier:identifer];
}
- (void)setSelectedClassWithIndex:(NSInteger)index {
//    [self.decorationView setSelectedClassWithIndex:index];
}

#pragma mark - notification event
- (void)reloadCollectionData:(NSNotification *)noti {
    NSDictionary *userInfo = noti.userInfo;
    BOOL change = NO;
    if (userInfo) {
        change = [userInfo boolForKey:@"change" defaultValue:NO];
    }
    
    if (change) {
        //变脸item数据源
//        NSArray *itemsArray = [self.dataHandle getDrawerDataArray];
//        [self.decorationView updatePageItems:itemsArray];
    }else {
//        [self.decorationView.collectionView reloadData];
    }
    
    NSArray<MDFaceDecorationItem *> *itemsArray = [self.dataHandle getDrawerDataArray][1];
    [self.newDecorationView updateDownloadingWithIsDownloading:itemsArray[0].isDownloading type:CellTypeGesture];
    if (!itemsArray[0].isDownloading) {
        [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[0].resourcePath isNotEmpty] type:CellTypeGesture];
    }

    [self.newDecorationView updateDownloadingWithIsDownloading:itemsArray[1].isDownloading type:CellTypeExpression];
    if (!itemsArray[1].isDownloading) {
        [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[1].resourcePath isNotEmpty] type:CellTypeExpression];
    }
    
    [self.newDecorationView updateDownloadingWithIsDownloading:itemsArray[2].isDownloading type:CellTypeEffect3D];
    if (!itemsArray[2].isDownloading) {
        [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[2].resourcePath isNotEmpty] type:CellTypeEffect3D];
    }
    
    [self.newDecorationView updateDownloadingWithIsDownloading:itemsArray[3].isDownloading type:CellTypeSegment];
    if (!itemsArray[3].isDownloading) {
        [self.newDecorationView updateHasResourceWithHasResource:[itemsArray[3].resourcePath isNotEmpty] type:CellTypeSegment];
    }
}

#pragma mark - MDFaceDecorationViewDelegate

//- (void)faceDecorationPageView:(MDFaceDecorationPageView *)pageView
//                     indexPath:(NSIndexPath *)indexPath
//                     withModel:(MDFaceDecorationItem *)cellModel {
//
//    if (![cellModel.identifier isNotEmpty] || cellModel.isDownloading) {
//        return;
//    }
//    //设置点击弹性
//    cellModel.clickedToBounce = YES;
//    //调用dataHandle处理item
//    [self.dataHandle drawerDidSelectedItem:cellModel];
//}

//清除选中变脸
//- (void)faceDecorationViewCleanDecoration:(MDFaceDecorationView *)view {
//    [self.dataHandle drawerDidCleanAllItem];
//}

#pragma mark - 显示 隐藏变脸抽屉View
- (BOOL)showAnimate
{
    if (self.isShowed || self.isAnimating) return NO;
    
    self.view.hidden = NO;
    self.show = YES;
    self.animating = YES;
    
    UIView* view = self.contentView;
    view.transform = CGAffineTransformMakeTranslation(0, view.height);
    [UIView animateWithDuration:0.5 delay:0 usingSpringWithDamping:0.7 initialSpringVelocity:0.5 options:UIViewAnimationOptionCurveEaseInOut animations:^{
        
        view.transform = CGAffineTransformIdentity;
    } completion:^(BOOL finished) {
        self.animating = NO;
    }];
    
    return YES;
}

- (void)hideAnimateWithCompleteBlock:(void(^)(void))completeBlock
{
    if (!self.isShowed || self.isAnimating) return;

    self.view.hidden = NO;
    self.show = NO;
    self.animating = YES;
    
    UIView* view = self.contentView;
    view.transform = CGAffineTransformIdentity;
    [UIView animateWithDuration:0.25 animations:^{
        view.transform = CGAffineTransformMakeTranslation(0, view.height);
    } completion:^(BOOL finished) {
        self.view.hidden = YES;
        self.animating = NO;
        if (completeBlock) {
            completeBlock();
        }
    }];
}

#pragma mark - lazy
- (UIView *)contentView {
    if(!_contentView){
        _contentView = [[UIView alloc] initWithFrame:self.view.bounds];
        _contentView.height += 50;
    }
    return _contentView;
}

//- (MDFaceDecorationView *)decorationView{
//
//    if(!_decorationView){
//        _decorationView = [[MDFaceDecorationView alloc] initWithFrame:self.view.bounds];
//        _decorationView.delegate = self;
//    }
//    return _decorationView;
//}

- (NewFaceDecorationView *)newDecorationView {
    if (!_newDecorationView) {
        _newDecorationView = [[NewFaceDecorationView alloc] initWithFrame:self.view.bounds];
        _newDecorationView.delegate = self;
    }
    return _newDecorationView;
}

- (UIVisualEffectView *)effectView {
    if(!_effectView) {
        _effectView = [[UIVisualEffectView alloc] initWithEffect:[UIBlurEffect effectWithStyle:UIBlurEffectStyleDark]];
        _effectView.frame = self.contentView.bounds;
        _effectView.layer.cornerRadius = 10.0f;
        _effectView.layer.masksToBounds = YES;
    }
    return _effectView;
}

#pragma mark - NewFaceDecorationViewDelegate Methods

- (void)selectedWithView:(NewFaceDecorationView *)view type:(enum CellType)type {
    //调用dataHandle处理item
    NSArray *itemsArray = [self.dataHandle getDrawerDataArray];
    MDFaceDecorationItem *cellModel = nil;
    switch (type) {
        case CellTypeGesture:
            cellModel = itemsArray[1][0];
            break;
        case CellTypeExpression:
            cellModel = itemsArray[1][1];
            break;
        case CellTypeEffect3D:
            cellModel = itemsArray[1][2];
            break;
        case CellTypeSegment:
            cellModel = itemsArray[1][3];
            break;
            
        default:
            break;
    }
    [self.dataHandle drawerDidSelectedItem:cellModel];

}

- (void)didClearWithView:(NewFaceDecorationView *)view {
    [self.dataHandle drawerDidCleanAllItem];
}

@end
