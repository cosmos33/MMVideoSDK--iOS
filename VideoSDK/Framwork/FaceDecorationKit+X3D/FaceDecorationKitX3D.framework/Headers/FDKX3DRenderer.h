//
//  FDK3DRenderer.h
//  Pods
//
//  Created by YuAo on 12/20/16.
//
//

#import <Foundation/Foundation.h>
#import <FaceDecorationKit/FDKProtocols.h>

NS_ASSUME_NONNULL_BEGIN

@interface FDKX3DRenderer : NSObject <FDK3DRendering>

@property (nonatomic,readonly,class) EAGLContext *sharedContext;

@end

NS_ASSUME_NONNULL_END
