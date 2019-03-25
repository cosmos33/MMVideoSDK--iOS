# RecordSDK 接口文档

短视频模块SDK, 用于录制视频，视频编辑，添加特效等功能。RecordSDK核心四大模块主要由基础模块，录制模块，视频编辑模块，图片编辑模块四大模块构成。包含了需要用到的工具类，滤镜，视频导出组件等重要基础功能。录制模块主要包含了视频录制相关操作，已经相关特效处理功能。视频编辑与图片编辑模块主要包含了视频(图片)编辑相关操作以及相关特效处理功能。

## 基本功能

### 初始化SDK

* 设置APPID

```objective-c
    + (void)initSDK:(NSString *)appID;
```

* 注册APP获取Token

```objective-c
    + (void)registerToken
```

* 添加回调函数。 selector 可添加 `MDRecordCallbackMessage` 类型的参数

```objective-c
+ (void) addCommandListener: (SEL) mSelctor target:(id) mTarget;
```

* 获取SDK version

```objective-c
+ (NSString *)version;
```

* 获取Token

```objective-c
    + (NSString *)appToken;
```

* 设置人脸识别预加载器

```objective-c
    + (void)setDetectorModelsPreloader:(id<MDRecordDetectorPreloader>)preloader;
```

## 录制模块

### 基本设置

* 获取显示视图

```objective-c
    @property (nonatomic, strong, readonly) UIView<MLPixelBufferDisplay> *previewView;
```

* 设置最大录制时长

```objective-c
    - (void)setMaxRecordDuration:(NSTimeInverval)duration;
```

* 设置生成视屏编码格式, 参数参考  `AVVideoCodecType`

```objective-c
    - (void)setVideoCodecKey:(NSString *)codeckey;
```

* 设置生成视频码率

```objective-c
    - (void)setVideoBitRate:(float)bitrate;
```

* 设置生成视频分辨率

```objective-c
    - (void)setVideoResolution:(CGSize)resolution;
```

* 设置生成视频填充模式(等比适应/等比填充/拉伸)，参数参考 `AVVideoScalingModeKey`

```objective-c
    - (void)setVideoScaleMode:(NSString *)scaleMode;
```

* 设置摄像头采样分辨率, 参考 `AVCaptureSessionPreset`

```objective-c
    - (void)setCameraPreset:(NSString *)preset;
```

* 设置摄像头初始位置

```objective-c
    - (void)setCameraPosition:(AVCaptureDevicePosition *)position;
```

* 初始化相机

```objective-c
    - (void)setupRecorder;
```

* 获取录制最大时长

```objective-c
    - (NSTimeInterval)recordDuration;
```

### 录制操作

* 设置闪光灯模式

```objective-c
    // 是否支持闪光灯
    - (BOOL)hasFlash;

    // 闪光灯模式
    - (NSArray *)supportFlashModes;

    // 设置闪光灯模式
    @property (nonatomic, assign) MDRecordCaptureFlashMode flashMode;
```

* 是否存在相机输入源

```objective-c
- (BOOL)hasVideoInput;
```

* 切换摄像头

```objective-c
    - (void)switchCameraPosition;
```

* 获取当前摄像头位置

```objective-c
@property (nonatomic, assign, readonly) AVCaptureDevicePosition cameraPosition;
```

* 摄像头聚焦

```objective-c
    - (void)focusCameraInPoint:(CGPoint)pointInCamera;
```

* 开启预览

```objective-c
    - (void)startCapturing;
```

* 暂停预览

```objective-c
    - (void)pauseCapturing;
```

* 结束预览

```objective-c
    - (void)stopCapturing;
```

* 拍照

```objective-c
    - (void)takePhoto;
```

* 拍照回调

```objective-c
    // 即将开始拍照
    @property (nonatomic, copy) void (^captureStillImageWillHandler)(void);

    // 拍照结果回调
    @property (nonatomic, copy) void (^captureStillImageHandler)(UIImage *image);

```

* 设置设备方向

```objective-c
@property (nonatomic, assign) UIDeviceOrientation outputOrientation;
```

* 是否可以录制

```objective-c
    - (BOOL)canStartRecording;
```

* 开始录制

```objective-c
    - (void)startRecording;
```

* 完成一段录制

```objective-c
    - (void)pauseRecording;
```

* 取消当前段录制

```objective-c
    - (void)cancelRecording;
```

* 结束录制

```objective-c
    - (void)stopVideoCaptureWithOutputURL:(NSURL *)URL
                    completionHandler:(void (^)(NSURL *videoFileURL, NSError *error))completionHandler;
```

* 获得分段数量

```objective-c
    - (NSInteger)savedSegmentCount;
```

* 删除最后一个分段

```objective-c
    - (void)deleteLastSavedSegment;
```

* 重置录制操作(移除所有已录制的视频片段以及录制状态)

```objective-c
    - (void)resetRecorder;
```

* 清除暂存文件

```objective-c
    - (void)cleanStashFile;
```

* 是否正在录制

```objective-c
    @property (nonatomic, readonly) BOOL isRecording;
```

* 获取当前录制时长

```objective-c
    @property (nonatomic, readonly) NSTimeInterval currentRecordingDuration;
```

* 获取变速后实际展示时长

```objective-c
    @property (nonatomic, readonly) NSTimeInterval currentRecordingPresentDuration;
```

* 是否正在合成视频

```objective-c
@property (nonatomic, assign, readonly) BOOL stopMerge;
```

* 录制进度回调

```objective-c
    @property (nonatomic, copy) void (^recordProgressChangedHandler)(double progress);
```

* 到达最大录制时长回调

```objective-c
    @property (nonatomic, copy) void (^recordDurationReachedHandler)(void);
```

* 导出视频进度回调

```objective-c
    @property (nonatomic, copy) void (^completeProgressUpdateHandler)(double progress);
```

* 录制片段增加/删除

```objective-c
@property (nonatomic,copy) void (^recordSegmentsChangedHandler)(NSArray *durations, NSArray *presentDurations, BOOL valid , MDRecordSegmentStatus segmentStatus)
```

```objective-c
    - (void)configFilterA:(MDRecordFilter *)filterA configFilterB:(MDRecordFilter *)filterB offset:(float)offset;
```

* 增加美颜滤镜/贴纸

```objective-c
    - (void)updateDecoration:(FDKDecoration *)decoration;
```

* 移除美颜/贴纸

```objective-c
- (void)removeDecoration;
```

* 调整贴纸自带音效音量

```objective-c
- (void)adjustStikcerVolume:(float)volume;
```

* 光膀子检测

```objective-c
// 是否开启光膀子检测
- (void)activateBarenessDetectorEnable:(BOOL)enable;
// 是否存在光膀子
- (BOOL)hasDetectorBareness;
// 发现光膀子时候的回调
- (void)setDetectBareness:(void (^)(void))detectBareness;
```

* 是否使用AI美颜功能 (iOS 10以上开启)

```objective-c
@property (nonatomic, assign) BOOL canUseAIBeautySetting;
```

* 是否启用瘦身长腿功能

```objective-c
@property (nonatomic, assign) BOOL canUseBodyThinSetting;
```

* 是否检测到人脸

```objective-c
@property (nonatomic, readonly) BOOL isFaceCaptured;
```

* 重置检测器状态

```objective-c
- (void)resetState;
```

* 清除贴纸缓存

```objective-c
    - (void)clean;
```

* 配乐

```objective-c
    // 音乐资源
    @property (nonatomic, strong) AVAsset *backgroundAudio;
```

* 美颜设置

```objective-c
- (void)setBeautyConfiguration:(CXBeautyConfiguration *)config;
```

* 美白

```objective-c
- (void)setSkinWhitenValue:(float)value;
```

* 磨皮

```objective-c
- (void)setSkinSmoothValue:(float)value;
```

* 大眼

```objective-c
    - (void)setBeautyBigEyeValue:(float)value;
```

* 瘦脸

```objective-c
    - (void)setBeautyThinFaceValue:(float)value;
```

* 瘦身

```objective-c
    - (void)setBeautyThinBodyValue:(float)value;
```

* 长腿

```objective-c
    - (void)setBeautyLenghLegValue:(float)value;
```

* 启用3D引擎

```objective-c
    - (void)runXESEngineWithDecorationRootPath:(NSString *)path;
```

* 变速

```objective-c
    // 设置变速因子 (0.2 - 4.0)
    - (void)setNextRecordSegmentSpeedVaryFactor:(CGFloat)factor;
    // 获取当前变速因子
    - (CGFloat)nextRecordSegmentSpeedVaryFactor;
    // 当前段是否允许变速
    - (void)speedVaryShouldAllow:(BOOL)isAllow;
    // 当前段是否存在变速效果
    - (BOOL)hasPerSpeedEffect;
```

## 视频编辑模块

### 视频编辑模块基本设置

* 加载视频

```objective-c
- (void)loadVideo:(AVAsset *)asset;
```

* 视频裁剪

```objective-c
- (void)setVideoTimeRange:(CMTimeRange)timeRange;
```

* 设置变速效果

```objective-c
- (void)setTimeRangeMappingEffects:(NSArray<id<MLTimeRangeMappingEffect>> *)timeRangeMappingEffects;
```

* 这是重复片段

```objective-c
- (void)setMediaSourceRepeatRange:(CMTimeRange)timeRange;
```

* 设置配乐

```objective-c
@property (nonatomic, strong) NSURL *backgroundAudioURL;
```

* 裁剪配乐

```objective-c
@property (nonatomic, assign) CMTimeRange backgroundAudioRange;
```

* 设置原音量

```objective-c
- (void)setSourceVolume:(float)volume;
```

* 设置配乐音量

```objective-c
- (void)setBackgroundMusicVolume:(float)volume;
```

* 合成视频

```objective-c
- (BOOL)compositeVideoWithError:(NSError **)error;
```

* 更新音频音量

```objective-c
- (void)updateAudioMix;
```

### 播放控制

* 开始播放

```objective-c
    - (void)play;
```

* 停止播放

```objective-c
    - (void)stop;
```

* 暂停播放

```objective-c
    - (void)pause;
```

* 重新开始播放

```objective-c
    - (void)replay;
```

* 获得视频展示页面

```objective-c
@property (nonatomic, readonly) UIViewController *playerViewController;
```

* 获取播放器

```objective-c
    @property (nonatomic, readonly) AVPlayer *player;
```

* 是否正在播放

```objective-c
    @property (nonatomic, readonly) BOOL isPlaying;
```

* seek到某一时间点

```objective-c
    - (void)seekTime:(float)time;
```

* 获取总时长

```objective-c
    - (NSTimeInverval)duration;
```

* 获得当前播放时间

```objective-c
   - (NSTimeInterval)getCurrentPlayTime;
```

* 设置播放器刷新频率(默认30帧每秒)

```objective-c
    - (void)setPlayerPerferredFPS:(int)fps;
```

* 获得视频渲染frame

```objective-c
@property (nonatomic, readonly) CGRect videoRenderFrame;
```

* 获得当前合成的视频

```objective-c
@property (nonatomic, readonly) AVComposition *composition;
```

* 等待视频渲染队列中所有任务完成

```objective-c
- (void)waitUntilAllOperationsAreFinished;
```

* 播放结束

```objective-c
    @property (nonatomic, copy) void(^ _Nullable playToEndTime)(AVPlayer *player);
```

* 播放进度

```objective-c
    @property (nonatomic, copy) void(^ _Nullable playerPeriodicTimeCallback)(CMTime time);
```

* 切换滤镜

```objective-c
    - (void)configFilterA:(MDRecordFilter *)filterA configFilterB:(MDRecordFilter *)filterB offset:(float)offset;
```

* 翻转特效滤镜

```objecitve-c
- (void)setReverse:(BOOL)reverse;
```

* 添加特效滤镜

```objective-c
    - (void)addSpecialFilter:(GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *)newTarget timeRange:(CMTimeRange)range;
```

* 移除最后一个特效滤镜

```objective-c
    - (void)deleteLastSpecialFilter;
```

* 移除所有特效滤镜

```objective-c
    - (void)deleteAllSpecialFilters;
```

* 更新某时刻特效滤镜起作用是时段

```objecitve-c
- (void)updateCurrentFilterWithTime:(CMTime)time timeRange:(CMTimeRange)timeRange;
```

* 获得当前所有添加的特效滤镜

```objecitve-c
- (NSArray<GPUImageOutput<GPUImageInput, MDSpecialFilterLifeStyleProtocol> *> *)specialFilters;
```

* 是否有添加特效滤镜

```objecitve-c
- (BOOL)hasSpecialFilter;
```

* 添加动态贴纸

```objective-c
    - (void)addDynamicSticker:(MDRecordDynamicSticker *)dynamicSticker;
```

* 删除动态贴纸

```objective-c
    - (void)removeDynamicSticker:(MDRecordDynamicSticker *)dynamicSticker;
```

* 增加美颜滤镜

```objective-c
    - (void)updateDecoration:(FDKDecoration *)decoration;
```

* 移除美颜

```objective-c
    - (void)removeDecoration;
```

* 美白

```objective-c
- (void)setSkinWhitenValue:(float)value;
```

* 磨皮

```objective-c
- (void)setSkinSmoothValue:(float)value;
```

* 大眼

```objective-c
    - (void)setBeautyBigEyeValue:(float)value;
```

* 瘦脸

```objective-c
    - (void)setBeautyThinFaceValue:(float)value;
```

* 瘦身

```objective-c
    - (void)setBeautyThinBodyValue:(float)value;
```

* 长腿

```objective-c
    - (void)setBeautyLenghLegValue:(float)value;
```

* 获取当前涂鸦图片

```objective-c
@property (nonatomic, readonly) UIImage *mosaicCanvasImage;
```

* 设置涂鸦或者马赛克

```objective-c
- (void)setGraffitiCanvasImage:(UIImage * _Nullable)graffitiCanvasImage mosaicCanvasImage:(UIImage * _Nullable)mosaicCanvasImage;
```

### 视频导出

* 图片融合

```objective-c
@property (nonatomic, strong) UIImage * _Nullable overlayImage;
```

* 设置导出码率

```objective-c
    @property (nonatomic, assign) float targetBitRate;
```

* 设置导出分辨率

```objective-c
    @property (nonatomic, assign) CGSize presentationSize;
```

* 设置视频旋转

```objective-c
@property (nonatomic, assign) CGAffineTransform videoPerferredTransform;
```

* 设置是否使用滤镜效果

```objective-c
    - (void)enableFilterEffect:(BOOL)enable;
```

* 开始导出

```objective-c
- (id<MDCancellable>)exportToURL:(NSURL *)url
                 progressHandler:(void(^ _Nullable)(double progress))progressHandler
                      completion:(void(^ _Nullable)(NSURL *url))completion
                         failure:(void(^ _Nullable)(NSError * _Nullable error))failure;
```

## 图片编辑模块

### 图片编辑模块基本设置

* 加载图片

```objective-c
    - (void)loadImage:(UIImage *)image completionHander:(void(^)(CVPixelBufferRef _Nullable, NSError * _Nullable))completion;
```

* 处理图片

```objective-c
    - (void)startProcess;
```

* 停止处理并释放资源

```objective-c
    - (void)stopProcess;
```

* 切换滤镜

```objective-c
    - (void)configFilterA:(MDRecordFilter *)filterA configFilterB:(MDRecordFilter *)filterB offset:(float)offset;
```

* 增加美颜滤镜

```objective-c
    - (void)updateDecoration:(FDKDecoration *)decoration;
```

* 美白

```objective-c
    - (void)setSkinWhitenValue:(float)value;
```

* 磨皮

```objective-c
    - (void)setSkinSmoothValue:(float)value;
```

* 大眼

```objective-c
    - (void)setBeautyBigEyeValue:(float)value;
```

* 瘦脸

```objective-c
    - (void)setBeautyThinFaceValue:(float)value;
```

* 瘦身

```objective-c
    - (void)setBeautyThinBodyValue:(float)value;
```

* 长腿

```objective-c
    - (void)setBeautyLenghLegValue:(float)value;
```

* 移除美颜

```objective-c
    - (void)removeDecoration;
```
