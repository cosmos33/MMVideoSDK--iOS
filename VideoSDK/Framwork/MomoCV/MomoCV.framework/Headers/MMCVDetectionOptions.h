//
//  MMCVDetectionOptions.h
//  Pods
//
//  Created by YuAo on 18/04/2017.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, MMCVImageOrientation) {
    MMCVImageOrientationUp, //0
    MMCVImageOrientationDown, // 180 deg rotation
    MMCVImageOrientationLeft, // 90 deg CCW
    MMCVImageOrientationRight // 90 deg CW
};

FOUNDATION_EXPORT double MMCVImageRotationDegreeFromOrientation(MMCVImageOrientation orientation);

NS_ASSUME_NONNULL_END
