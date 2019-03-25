//
//  XSKGLDisplayView.h
//  XEScene+Renderer
//
//  Created by momo783 on 07/05/2018.
//

#import "XSKTouchView.h"
#import <CoreMedia/CoreMedia.h>

@protocol XSKGLDisplayViewDataOutputDelegate;

@interface XSKGLDisplayView : XSKTouchView

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithFrame:(CGRect)frame;

@property(readonly) NSUInteger rendersSquence;

@property(nonatomic, assign) CGSize renderSize;    //defalut initial viewSize*nativeScale

@property(nonatomic, assign) NSUInteger frameRate; //defalut is 30

@property(nonatomic, weak) id <XSKGLDisplayViewDataOutputDelegate> delegate;

@property(nonatomic, readonly) CGFloat nativeScale;

- (void)shot:(void (^)(UIImage *))callback;

- (void)pause;

- (void)resume;

- (void)updateRenderID:(NSString *)renderID;

@end

@protocol XSKGLDisplayViewDataOutputDelegate <NSObject>
@optional
- (void)displayView:(XSKGLDisplayView *)displayView didOutputVideoPixelBuffer:(CVPixelBufferRef)pixelBuffer timinginfo:(CMSampleTimingInfo)timingInfo;
@end


typedef XSKGLDisplayView XESRenderDisplayView;

@protocol CVFaceFeature;

@interface XSKGLDisplayView (DEPRECATED)

- (void)updateFaceFeature:(id <CVFaceFeature>)faceFeature NS_DEPRECATED_IOS(9.0, 11.0, "Use +[XSKEventDispatcher updateFaceFeature:] instead.");

- (void)setupEngine:(NSString *)path NS_DEPRECATED_IOS(9.0, 11.0, "Use -[XSKEngine configResourcePath:] && -[XSKEngine runEngine] instead.");

- (void)destoryEngine NS_DEPRECATED_IOS(9.0, 11.0, "Use -[XSKEngine endRunEngine:] instead.");

- (void)loadScene:(NSString *)relativePath sceneID:(NSString *)sceneID NS_DEPRECATED_IOS(9.0, 11.0, "Use -[XSKEngine loadSceneWithRelatviePath:sceneID:] instead.");

- (void)unloadScene:(NSString *)sceneID NS_DEPRECATED_IOS(9.0, 11.0, "Use -[XSKEventDispatcher unloadSceneWithSceneID:] instead.");

@end
