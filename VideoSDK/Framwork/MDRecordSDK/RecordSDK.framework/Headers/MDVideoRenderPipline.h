//
//  MDVideoRenderPipline.h
//  MomoChat
//
//  Created by sunfei on 2018/12/28.
//  Copyright © 2018 wemomo.com. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MDProcessImageProtocol.h"
#import "MDVideoRenderFilter.h"
#import "MDVideoDetectorPipline.h"
#import <FaceDecorationKit/FDKDecoration.h>

NS_ASSUME_NONNULL_BEGIN

@interface MDVideoRenderPipline : NSObject <MDProcessImageProtocol>

@property (nonatomic, readonly) MDVideoRenderFilter *renderFilter;
@property (nonatomic, readonly) MDVideoDetectorPipline *detector;

- (void)updateDecoration:(FDKDecoration * _Nullable)decoration;

@end

NS_ASSUME_NONNULL_END
