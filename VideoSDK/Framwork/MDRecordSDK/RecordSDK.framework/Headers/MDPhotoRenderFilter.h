//
//  MDPhotoRenderFilter.h
//  MDRecordSDK
//
//  Created by sunfei on 2018/11/28.
//

#import <Foundation/Foundation.h>
#import <FaceDecorationKit/FDKDecoration.h>
#import <FaceDecorationKit/FDKDecorationFilterUpdating.h>
#import <FaceDecorationKitGPUImage/FDKDecorationFilter.h>
#import "MDProcessImageProtocol.h"
#import "MDRecordFilter.h"

NS_ASSUME_NONNULL_BEGIN

@interface MDPhotoRenderFilter : NSObject <MDProcessImageProtocol, FDKDecorationFilterUpdating>

- (instancetype)init;
- (instancetype)initWithFDKDecorationFilterOptions:(FDKDecorationFilterOptions *)options;

@property (nonatomic, strong) FDKDecoration * _Nullable decoration;

@property (nonatomic, copy) MDRecordFilter *slidingMDFilterA;
@property (nonatomic, copy) MDRecordFilter *slidingMDFilterB;
@property (nonatomic, assign) float slidingOffset;

@end

NS_ASSUME_NONNULL_END
