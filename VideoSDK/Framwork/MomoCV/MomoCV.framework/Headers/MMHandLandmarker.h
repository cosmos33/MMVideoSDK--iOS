//
//  MMHandLandmarker.h
//  MomoCV
//
//  Created by wuzhijia on 2018/7/18.
//

#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#import "MMBodyJoint.h"
#import "MMHandFeature.h"

NS_ASSUME_NONNULL_BEGIN

@interface MMHandLandmarkerOptions : NSObject

@property (nonatomic) BOOL useTracking;         // default true

@property (nonatomic) BOOL useCpuOnly;          // default false

@property (nonatomic) GLKMatrix4 projectMatrix;

@property (nonatomic) BOOL detect3dLandmark;    // default true

@property (nonatomic) BOOL detectSingleFrame;   // default false

@end


@interface MMHandLandmarker : NSObject

@property (nonatomic, readonly) NSURL *modelURL;

- (instancetype)init NS_UNAVAILABLE;

- (nullable instancetype)initWithModelBundle:(nullable NSBundle *)bundle error:(NSError **)error ;

- (nullable instancetype)initWithModelURL:(nullable NSURL*)modelURL error:(NSError **)error NS_DESIGNATED_INITIALIZER;

- (nullable MMHandFeature *)handInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer options:(MMHandLandmarkerOptions*)options;

- (nullable MMHandFeature *)handInfosInPixelBuffer:(CVPixelBufferRef)pixelBuffer handFeature:(nullable MMHandFeature *)handFeature options:(MMHandLandmarkerOptions*)options;

@end

CF_EXTERN_C_BEGIN
CF_EXPORT void MMCVDrawHandJointConnectionInBGRAPixelBuffer(CVPixelBufferRef pixelBuffer, NSArray<MMJoint *> *joints);
CF_EXTERN_C_END

NS_ASSUME_NONNULL_END
