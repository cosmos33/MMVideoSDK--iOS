//
// Created by momo783 on 06/08/2018.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <GLKit/GLKit.h>

@protocol CVFaceFeature <NSObject>

@property (nonatomic,readonly) NSInteger trackingIdentifier;

@property (nonatomic,readonly) CGRect bounds;

@property (nonatomic,readonly) double pitch;
@property (nonatomic,readonly) double yaw;
@property (nonatomic,readonly) double roll;

@property (nonatomic,readonly) CGSize imageSize;

@property (nonatomic,readonly) GLKMatrix3 cameraMatrix;
@property (nonatomic,readonly) GLKMatrix3 rotationMatrix;

@property (nonatomic,readonly) GLKVector3 rotationVector;
@property (nonatomic,readonly) GLKVector3 translationVector;

@property (nonatomic,readonly) GLKMatrix4 projectionMatrix;
@property (nonatomic,readonly) GLKMatrix4 modelViewMatrix;


@property (nonatomic,readonly) GLKVector3 facerigEulerVector;

@property (nonatomic,readonly) NSArray <NSNumber *> *facerigStates;

@property (nonatomic,readonly,copy) NSArray<NSValue *> *landmarks;

@end

@protocol CVFacialExpression <NSObject>

@property (nonatomic,readonly) NSInteger type;

@property (nonatomic,readonly) float amount;

@end

@protocol CVExpression <NSObject>

@property (nonatomic, readonly) NSInteger leftEye;
@property (nonatomic, readonly) NSInteger rightEye;

@property (nonatomic, readonly) NSInteger head;
@property (nonatomic, readonly) NSInteger neck;

@property (nonatomic, readonly) NSInteger mouth;

@end

@protocol CVBodyJoint <NSObject>

@property (nonatomic,readonly) CGPoint location;

@property (nonatomic,readonly) float score;

@property (nonatomic,readonly) GLKVector3 location3D;

@property (nonatomic,readonly) CGPoint location3DTo2D;

@end

@protocol CVBodyFeature <NSObject>

@property (nonatomic,copy,readonly) NSArray<id<CVBodyJoint>> *joints;

@end

@protocol CVGesture <NSObject>

@property (nonatomic,readonly) float score;

@property (nonatomic,readonly) NSString *type;

@property (nonatomic,readonly) CGRect bounds;

@end

@protocol CVHandFeature <NSObject>

@property (nonatomic,readonly) NSInteger trackingId;

@property (nonatomic,readonly) NSArray<id<CVGesture>> * gestures;

@property (nonatomic,readonly) NSArray<id<CVBodyJoint>> *landmarks;

@property (nonatomic,readonly) NSArray<NSNumber*> * params3D;

@end

@protocol CVObjectFeature <NSObject>

@property (nonatomic,copy,readonly) NSString *type;

@property (nonatomic,readonly) CGRect bounds;

@property (nonatomic,readonly) float score;

@end

