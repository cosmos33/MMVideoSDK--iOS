//
//  MDImageRenderPipline.h
//  MDRecordSDK
//
//  Created by sunfei on 2018/11/26.
//

#import <Foundation/Foundation.h>
#import "MDProcessImageProtocol.h"
#import "MDImageDetectorProtocol.h"
#import <FaceDecorationKit/FDKDecorationFilterUpdating.h>

NS_ASSUME_NONNULL_BEGIN

@interface MDImageRenderPipline : NSObject <MDProcessImageProtocol>

@property (nonatomic, strong) id<MDProcessImageProtocol, FDKDecorationFilterUpdating> filter;
@property (nonatomic, strong) id<MDImageDetectorProtocol> detector;

@end

NS_ASSUME_NONNULL_END
