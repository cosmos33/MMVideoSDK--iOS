//
//  MMFaceCluster.h
//  MomoCV
//
//  Created by momo783 on 21/01/2018.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface MMFaceNode : NSObject

@property (nonatomic, assign) NSUInteger faceId;

@property (nonatomic, assign) CGRect faceRect;

@property (nonatomic, strong) NSArray <NSNumber*> *feature;

@property (nonatomic, copy) NSString *imgId;

@property (nonatomic, assign) NSTimeInterval takeTime;

@property (nonatomic, assign) NSTimeInterval modifyTime;

@property (nonatomic, assign) double yaw;

@property (nonatomic, assign) double picth;

@property (nonatomic, assign) double roll;

@end

@interface MMClusterNode : NSObject

@property (nonatomic, assign) NSUInteger clusterId;

@property (nonatomic, strong) NSArray <NSNumber *> *faceIds;

@property (nonatomic, strong) NSArray <NSNumber *> *representFaceIds;

@end

@interface MMFaceCluster : NSObject

- (instancetype)init NS_UNAVAILABLE;

+ (instancetype)defaultCluster;

- (NSArray <MMClusterNode *>*)processIncrementCluster:(NSArray <MMClusterNode *>*)clusters faceNode:(NSArray <MMFaceNode *>*)faces;

@end

NS_ASSUME_NONNULL_END
