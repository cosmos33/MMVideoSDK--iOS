//
//  MDVideoDetectorPipline.h
//  RecordSDK
//
//  Created by sunfei on 2018/11/30.
//  Copyright © 2018 sunfei. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MDImageDetectorProtocol.h"
#import <FaceDecorationKit/FDKDecoration.h>
#import <FaceDecorationKit/FDKDecorationFilterUpdating.h>

NS_ASSUME_NONNULL_BEGIN

@interface MDVideoDetectorPipline : NSObject <MDImageDetectorProtocol>

- (instancetype)init;

- (void)thinBodyConfiguration:(FDKDecoration *)decoration;

@property (nonatomic, assign) BOOL canUseBodyThinSetting;
@property (nonatomic, readonly) FDKDecorationFilterUpdateRequest *result;

@end

NS_ASSUME_NONNULL_END
