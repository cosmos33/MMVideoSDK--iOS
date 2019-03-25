//
//  MDImageDetectorOptions.h
//  CXBeautyKit
//
//  Created by sunfei on 2018/11/26.
//

#import <Foundation/Foundation.h>
#import <MomoCV/MMCVDetectionOptions.h>

NS_ASSUME_NONNULL_BEGIN

@protocol MDImageDetectorOptions <NSObject>

@property (nonatomic) MMCVImageOrientation orientation;

@end

NS_ASSUME_NONNULL_END
