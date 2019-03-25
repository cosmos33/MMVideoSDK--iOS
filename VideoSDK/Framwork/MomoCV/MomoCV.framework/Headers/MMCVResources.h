//
//  MMFaceCoreResources.h
//  MomoCVDemo
//
//  Created by YuAo on 4/25/16.
//  Copyright © 2016 Momo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSBundle * MMCVResourcesBundle(void);

FOUNDATION_EXPORT NSURL * MMCVModelURLForBundle(NSBundle * _Nullable bundle, NSString *extension);

NS_ASSUME_NONNULL_END
