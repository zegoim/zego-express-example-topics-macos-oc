//
//  ZegoExpressDefines.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVFoundation.h>

#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#define ZGView UIView
#define ZGImage UIImage
#elif TARGET_OS_OSX
#import <AppKit/AppKit.h>
#define ZGView NSView
#define ZGImage NSImage
#endif

NS_ASSUME_NONNULL_BEGIN

@class ZegoMixerStartResult;
@protocol ZegoMediaPlayerEventHandler;
@protocol ZegoMediaPlayerVideoHandler;
@protocol ZegoMediaPlayerAudioHandler;

/// 更新流附加信息接口的回调 block
typedef void(^ZegoPublisherSetStreamExtraInfoCallback)(int errorCode);

/// 添加/删除转推 CDN 接口的回调 block
typedef void(^ZegoPublisherUpdateCDNURLCallback)(int errorCode);

/// 开始混流任务接口的回调 block
typedef void(^ZegoMixerStartCallback)(ZegoMixerStartResult *result);

/// 发送房间聊天消息的回调 block
typedef void(^ZegoIMSendBroadcastMessageCallback)(int errorCode);

/// 发送房间自定义信令的回调 block
typedef void(^ZegoIMSendCustomCommandCallback)(int errorCode);

/// 播放器加载资源完成回调
typedef void(^ZegoMediaPlayerLoadResourceCallback)(int errorCode);

/// 设置指定播放进度回调
typedef void(^ZegoMediaPlayerSeekToCallback)(int errorCode);


/// 使用场景
typedef NS_ENUM(NSUInteger, ZegoScenario) {
    /// 通用场景
    ZegoScenarioGeneral = 0,
};


/// 语言
typedef NS_ENUM(NSUInteger, ZegoLanguage) {
    /// 英文
    ZegoLanguageEnglish = 0,
    /// 中文
    ZegoLanguageChinese = 1,
};


/// 房间状态
typedef NS_ENUM(NSUInteger, ZegoRoomState) {
    /// 未连接状态，在登陆房间前和退出房间之后进入该状态。如果登陆房间的过程出现稳态异常，例如 AppID 和 AppSign 不正确，或者有相同用户名在其他地方登陆导致本端被 KickOut，都会进入该状态
    ZegoRoomStateDisconnected = 0,
    /// 正在请求连接状态，登陆房间动作执行成功后会进入此状态。通常通过该状态进行应用界面的展示。如果因为网络质量不佳产生的中断， SDK 会进行内部重试，也会回到正在请求连接状态
    ZegoRoomStateConnecting = 1,
    /// 连接成功状态，进入该状态表示登陆房间已经成功，用户可以正常收到房间内的用户和流信息增删的回调通知
    ZegoRoomStateConnected = 2,
};


/// 视频渲染模式
typedef NS_ENUM(NSUInteger, ZegoViewMode) {
    /// 等比缩放，可能有黑边
    ZegoViewModeAspectFit = 0,
    /// 等比缩放填充整个 View ，可能有部分被裁减
    ZegoViewModeAspectFill = 1,
    /// 填充整个 View，图像可能被拉伸
    ZegoViewModeScaleToFill = 2,
};


/// 预览或拉流端的镜像模式
typedef NS_ENUM(NSUInteger, ZegoVideoMirrorMode) {
    /// 只有本地预览时才是镜像画面，默认采用此模式
    ZegoVideoMirrorModeOnlyPreviewMirror = 0,
    /// 本地预览和拉流端看到的视频都是镜像画面
    ZegoVideoMirrorModeBothMirror = 1,
    /// 本地预览和拉流端看到的视频都不是镜像画面
    ZegoVideoMirrorModeNoMirror = 2,
    /// 只有拉流端看到的视频才是镜像画面
    ZegoVideoMirrorModeOnlyPublishMirror = 3,
};


/// 推流状态
typedef NS_ENUM(NSUInteger, ZegoPublisherState) {
    /// 未推流状态，在推流前处于该状态。如果推流过程出现稳态的异常，例如 AppID 和 AppSign 不正确，或者如果其他用户已经在推送流，推送相同流 ID 的流会失败，都会进入未推流状态
    ZegoPublisherStateNoPublish = 0,
    /// 正在请求推流状态，推流操作执行成功后会进入正在请求推流状态，通常通过该状态进行应用界面的展示。如果因为网络质量不佳产生的中断，SDK 会进行内部重试，也会回到正在请求推流状态
    ZegoPublisherStatePublishRequesting = 1,
    /// 正在推流状态，进入该状态表明推流已经成功，用户可以正常通信
    ZegoPublisherStatePublishing = 2,
};


/// 分辨率设置
typedef NS_ENUM(NSUInteger, ZegoResolution) {
    /// 设置分辨率为 180x320，默认采用 15 fps，码率 300000 bps
    ZegoResolution180x320 = 0,
    /// 设置分辨率为 270x480，默认采用 15 fps，码率 400000 bps
    ZegoResolution270x480 = 1,
    /// 设置分辨率为 360x640，默认采用 15 fps，码率 600000 bps
    ZegoResolution360x640 = 2,
    /// 设置分辨率为 540x960，默认采用 15 fps，码率 1200000 bps
    ZegoResolution540x960 = 3,
    /// 设置分辨率为 720x1280，默认采用 15 fps，码率 1500000 bps
    ZegoResolution720x1280 = 4,
    /// 设置分辨率为 1080x1920，默认采用 15 fps，码率 3000000 bps
    ZegoResolution1080x1920 = 5,
};


/// 推流端采集首帧事件
typedef NS_ENUM(NSUInteger, ZegoPublisherFirstFrameEvent) {
    /// 推流端采集到音频首帧事件
    ZegoPublisherFirstFrameEventAudioCaptured = 0,
    /// 推流端采集到视频首帧事件
    ZegoPublisherFirstFrameEventVideoCaptured = 1,
};


/// 流质量等级
typedef NS_ENUM(NSUInteger, ZegoStreamQualityLevel) {
    /// 质量极好
    ZegoStreamQualityLevelExcellent = 0,
    /// 质量好
    ZegoStreamQualityLevelGood = 1,
    /// 质量正常
    ZegoStreamQualityLevelMedium = 2,
    /// 质量差
    ZegoStreamQualityLevelBad = 3,
    /// 质量异常
    ZegoStreamQualityLevelDie = 4,
};


/// 延迟模式
typedef NS_ENUM(NSUInteger, ZegoLatencyMode) {
    /// 普通延迟模式
    ZegoLatencyModeNormal = 0,
    /// 低延迟模式，无法用于 RTMP 流 
    ZegoLatencyModeLow = 1,
    /// 普通延迟模式，最高码率可达 192 kbps
    ZegoLatencyModeNormal2 = 2,
    /// 低延迟模式，无法用于 RTMP 流。相对与 ZegoLatencyModeLow 而言，CPU 开销稍低
    ZegoLatencyModeLow2 = 3,
    /// 低延迟模式，无法用于 RTMP 流。支持 WebRTC 必须使用此模式
    ZegoLatencyModeLow3 = 4,
    /// 普通延迟模式
    ZegoLatencyModeNormal3 = 5,
};


/// 声道数量
typedef NS_ENUM(NSUInteger, ZegoAudioChannelType) {
    /// 单声道
    ZegoAudioChannelTypeMono = 0,
    /// 双声道
    ZegoAudioChannelTypeStereo = 1,
};


/// 回声消除模式
typedef NS_ENUM(NSUInteger, ZegoAECMode) {
    /// 激进的回声抵消，可能会影响音质稍微明显，但是回声会消除得很干净
    ZegoAECModeAggressive = 0,
    /// 适度的回声抵消，就是可能会稍微影响一点点音质，但是残留的回声会更少
    ZegoAECModeMedium = 1,
    /// 舒适的回声抵消，就是回声抵消基本不会影响声音的音质，可能有时会残留一点回声，但不会影响正常听音
    ZegoAECModeSoft = 2,
};


/// 拉流状态
typedef NS_ENUM(NSUInteger, ZegoPlayerState) {
    /// 未拉流状态，在拉流前处于该状态。如果拉流过程出现稳态的异常，例如 AppID 和 AppSign 不正确，都会进入未拉流状态
    ZegoPlayerStateNoPlay = 0,
    /// 正在请求拉流状态，拉流操作执行成功后会进入正在请求拉流状态，通常通过该状态进行应用界面的展示。如果因为网络质量不佳产生的中断，SDK 会进行内部重试，也会回到正在请求拉流状态
    ZegoPlayerStatePlayRequesting = 1,
    /// 正在拉流状态，进入该状态表明拉流已经成功，用户可以正常通信
    ZegoPlayerStatePlaying = 2,
};


/// 拉流媒体事件
typedef NS_ENUM(NSUInteger, ZegoPlayerMediaEvent) {
    /// 拉流端出现音频卡顿事件
    ZegoPlayerMediaEventAudioBreakOccur = 0,
    /// 拉流端音频卡顿事件结束
    ZegoPlayerMediaEventAudioBreakResume = 1,
    /// 拉流端出现视频卡顿事件
    ZegoPlayerMediaEventVideoBreakOccur = 2,
    /// 拉流端视频卡顿事件结束
    ZegoPlayerMediaEventVideoBreakResume = 3,
};


/// 拉流首帧事件
typedef NS_ENUM(NSUInteger, ZegoPlayerFirstFrameEvent) {
    /// 拉流端拉取到音频首帧事件
    ZegoPlayerFirstFrameEventAudioRcv = 0,
    /// 拉流端拉取到视频首帧事件
    ZegoPlayerFirstFrameEventVideoRcv = 1,
    /// 拉流端视频首帧渲染完成事件
    ZegoPlayerFirstFrameEventVideoRender = 2,
};


/// 更新类型
typedef NS_ENUM(NSUInteger, ZegoUpdateType) {
    /// 添加
    ZegoUpdateTypeAdd = 0,
    /// 删除
    ZegoUpdateTypeDelete = 1,
};


/// 转推 CDN 状态
typedef NS_ENUM(NSUInteger, ZegoStreamRelayCDNState) {
    /// 未转推状态，在转推前处于该状态。如果转推过程出现稳态的异常，例如 转推地址 不正确，都会进入未转推状态
    ZegoStreamRelayCDNStateStop = 0,
    /// 正在转推状态，进入该状态表明转推已成功
    ZegoStreamRelayCDNStateStart = 1,
    /// 正在请求转推状态，转推操作执行成功后会进入正在请求转推状态，通常通过该状态进行应用界面的展示。如果因为网络质量不佳产生的中断，SDK 会进行内部重试，也会回到正在转推状态
    ZegoStreamRelayCDNStateRetry = 2,
};


/// 转发 CDN 状态改变原因
typedef NS_ENUM(NSUInteger, ZegoStreamRelayCDNUpdateReason) {
    /// 无
    ZegoStreamRelayCDNUpdateReasonNone = 0,
    /// 服务器错误
    ZegoStreamRelayCDNUpdateReasonServerError = 1,
    /// 握手失败
    ZegoStreamRelayCDNUpdateReasonHandshakeFailed = 2,
    /// 接入点错误
    ZegoStreamRelayCDNUpdateReasonAccessPointError = 3,
    /// 创建流失败
    ZegoStreamRelayCDNUpdateReasonCreateStreamFailed = 4,
    /// BAD NAME
    ZegoStreamRelayCDNUpdateReasonBadName = 5,
    /// CDN 服务器主动断开
    ZegoStreamRelayCDNUpdateReasonCDNServerDisconnected = 6,
    /// 主动断开
    ZegoStreamRelayCDNUpdateReasonDisconnected = 7,
};


/// 美颜特性
typedef NS_OPTIONS(NSUInteger, ZegoBeautifyFeature) {
    /// 无美颜
    ZegoBeautifyFeatureNone = 0,
    /// 磨皮
    ZegoBeautifyFeaturePolish = 1 << 0,
    /// 锐化
    ZegoBeautifyFeatureWhiten = 1 << 1,
    /// 皮肤美白
    ZegoBeautifyFeatureSkinWhiten = 1 << 2,
    /// 全屏美白
    ZegoBeautifyFeatureSharpen = 1 << 3,
};


/// 远端设备状态
typedef NS_ENUM(NSUInteger, ZegoRemoteDeviceState) {
    /// 设备开启
    ZegoRemoteDeviceStateOpen = 0,
    /// 设备关闭：一般性设备错误
    ZegoRemoteDeviceStateGenericError = 1,
    /// 设备关闭：无效的设备 ID
    ZegoRemoteDeviceStateInvalidID = 2,
    /// 设备关闭：无权限
    ZegoRemoteDeviceStateNoAuthorization = 3,
    /// 设备关闭：采集帧率为 0
    ZegoRemoteDeviceStateZeroFPS = 4,
    /// 设备关闭：设备被占用
    ZegoRemoteDeviceStateInUseByOther = 5,
    /// 设备关闭：设备未插入或被拔出
    ZegoRemoteDeviceStateUnplugged = 6,
    /// 设备关闭：由于系统原因需要重启后才能进行下一次修改，否则重新打开也不生效
    ZegoRemoteDeviceStateRebootRequired = 7,
    /// 设备关闭：系统媒体服务停止，如 iOS 平台下，当系统检测到当前压力巨大（如播放大量动画），则有可能会将媒体相关服务全部停用
    ZegoRemoteDeviceStateSystemMediaServicesLost = 8,
    /// 设备关闭：禁用采集
    ZegoRemoteDeviceStateDisable = 9,
    /// 设备关闭：远端设备被静音
    ZegoRemoteDeviceStateMute = 10,
    /// 设备关闭：设备被中断，如电话事件打断等
    ZegoRemoteDeviceStateInterruption = 11,
    /// 设备关闭：用户 App 退到后台
    ZegoRemoteDeviceStateInBackground = 12,
    /// 设备关闭：当前前台同时存在多个 App，如 iPad 应用分屏下，系统会禁止所有应用使用摄像头
    ZegoRemoteDeviceStateMultiForegroundApp = 13,
    /// 设备关闭：系统处于高负载压力下，可能导致设备异常
    ZegoRemoteDeviceStateBySystemPressure = 14,
};


/// 音频设备类型
typedef NS_ENUM(NSUInteger, ZegoAudioDeviceType) {
    /// 音频输入设备
    ZegoAudioDeviceTypeInput = 0,
    /// 音频输出设备
    ZegoAudioDeviceTypeOutput = 1,
};


/// 混流内容类型
typedef NS_ENUM(NSUInteger, ZegoMixerInputContentType) {
    /// 音频混流内容类型
    ZegoMixerInputContentTypeAudio = 0,
    /// 视频混流内容类型
    ZegoMixerInputContentTypeVideo = 1,
};


/// 视频采集缩放时机
typedef NS_ENUM(NSUInteger, ZegoCapturePipelineScaleMode) {
    /// 采集后立即进行缩放，默认
    ZegoCapturePipelineScaleModePre = 0,
    /// 编码时进行缩放
    ZegoCapturePipelineScaleModePost = 1,
};


/// 视频帧格式
typedef NS_ENUM(NSUInteger, ZegoVideoFrameFormat) {
    /// 未知格式，将取平台默认值
    ZegoVideoFrameFormatUnknown = 0,
    /// I420 (YUV420Planar) 格式
    ZegoVideoFrameFormatI420 = 1,
    /// NV12 (YUV420SemiPlanar) 格式
    ZegoVideoFrameFormatNV12 = 2,
    /// NV32 (YUV420SemiPlanar) 格式
    ZegoVideoFrameFormatNV21 = 3,
    /// BGRA32 格式
    ZegoVideoFrameFormatBGRA32 = 4,
    /// RGBA32 格式
    ZegoVideoFrameFormatRGBA32 = 5,
    /// ARGB32 格式
    ZegoVideoFrameFormatARGB32 = 6,
    /// ABGR32 格式
    ZegoVideoFrameFormatABGR32 = 7,
    /// I422 (YUV422Planar) 格式
    ZegoVideoFrameFormatI422 = 8,
};


/// 视频帧数据类型
typedef NS_ENUM(NSUInteger, ZegoVideoBufferType) {
    /// 未知类型
    ZegoVideoBufferTypeUnknown = 0,
    /// 裸数据类型视频帧
    ZegoVideoBufferTypeRawData = 1,
    /// OpenGL Texture 2D 类型视频帧
    ZegoVideoBufferTypeGLTexture2D = 3,
    /// CVPixelBuffer 类型视频帧
    ZegoVideoBufferTypeCVPixelBuffer = 4,
};


/// 视频帧格式系列
typedef NS_ENUM(NSUInteger, ZegoVideoFrameFormatSeries) {
    /// RGB 系列
    ZegoVideoFrameFormatSeriesRGB = 0,
    /// YUV 系列
    ZegoVideoFrameFormatSeriesYUV = 1,
};


/// 视频帧翻转模式
typedef NS_ENUM(NSUInteger, ZegoVideoFlipMode) {
    /// 不翻转
    ZegoVideoFlipModeNone = 0,
    /// X 轴翻转
    ZegoVideoFlipModeX = 1,
};


/// 音频配置类型
typedef NS_ENUM(NSUInteger, ZegoAudioConfigPreset) {
    /// 低延迟-基础音质
    ZegoAudioConfigPresetLowLatencyBasicQuality = 0,
    /// 低延迟-标准音质
    ZegoAudioConfigPresetLowLatencyStandardQuality = 1,
    /// 低延迟-标准音质-双声道
    ZegoAudioConfigPresetLowLatencyStandardQualityStereo = 2,
    /// 低延迟-高音质
    ZegoAudioConfigPresetLowLatencyHighQuality = 3,
    /// 低延迟-高音质-双声道
    ZegoAudioConfigPresetLowLatencyHighQualityStereo = 4,
    /// 普通延迟-标准音质
    ZegoAudioConfigPresetNormalLatencyStandardQuality = 5,
    /// 普通延迟-标准音质-双声道
    ZegoAudioConfigPresetNormalLatencyStandardQualityStereo = 6,
    /// 普通延迟-高音质
    ZegoAudioConfigPresetNormalLatencyHighQuality = 7,
    /// 普通延迟-高音质-双声道
    ZegoAudioConfigPresetNormalLatencyHighQualityStereo = 8,
};


/// 播放器状态
typedef NS_ENUM(NSUInteger, ZegoMediaPlayerState) {
    /// 不在播放
    ZegoMediaPlayerStateNoPlay = 0,
    /// 播放中
    ZegoMediaPlayerStatePlaying = 1,
    /// 暂停播放
    ZegoMediaPlayerStatePausing = 2,
    /// 播放结束
    ZegoMediaPlayerStatePlayEnded = 3,
};


/// 播放器网络事件
typedef NS_ENUM(NSUInteger, ZegoMediaPlayerNetworkEvent) {
    /// 网络资源播放不畅，开始尝试缓存数据
    ZegoMediaPlayerNetworkEventBufferBegin = 0,
    /// 网络资源可以顺畅播放
    ZegoMediaPlayerNetworkEventBufferEnded = 1,
};


/// 日志配置
@interface ZegoLogConfig : NSObject

/// 日志路径，默认为 [NSCachesDirectory]/ZegoLogs/
@property (nonatomic, copy) NSString *logPath;

/// 日志文件的大小上限 (Bytes)，默认为 5MB (5 * 1024 * 1024 Bytes)
@property (nonatomic, assign) unsigned long long logSize;

@end


/// 自定义视频采集配置
@interface ZegoCustomVideoCaptureConfig : NSObject

/// 自定义视频采集视频帧数据类型
@property (nonatomic, assign) ZegoVideoBufferType bufferType;

@end


/// 自定义视频渲染配置
@interface ZegoCustomVideoRenderConfig : NSObject

/// 自定义视频渲染视频帧数据类型
@property (nonatomic, assign) ZegoVideoBufferType bufferType;

/// 自定义视频渲染视频帧数据格式
@property (nonatomic, assign) ZegoVideoFrameFormatSeries frameFormatSeries;

/// 是否在自定义视频渲染的同时，引擎也渲染
@property (nonatomic, assign) BOOL enableEngineRender;

@end


/// 引擎进阶配置
@interface ZegoEngineConfig : NSObject

/// 日志配置，不设则使用默认配置，日志路径默认为 [NSCachesDirectory]/ZegoLogs/，日志大小上限默认为 5MB
@property (nonatomic, strong, nullable) ZegoLogConfig *logConfig;

/// 自定义视频采集配置，不设则默认不开启自定义视频采集
@property (nonatomic, strong, nullable) ZegoCustomVideoCaptureConfig *customVideoCaptureConfig;

/// 自定义视频渲染配置，不设则默认不开启自定义视频渲染
@property (nonatomic, strong, nullable) ZegoCustomVideoRenderConfig *customVideoRenderConfig;

/// 隐藏功能开关，不设则默认不使用任何隐藏功能
@property (nonatomic, copy, nullable) NSDictionary<NSString *, NSString *> *advancedConfig;

@end


/// 房间配置
@interface ZegoRoomConfig : NSObject

/// 房间最大用户数量，默认无限制
@property (nonatomic, assign) unsigned int maxMemberCount;

/// 是否开启用户进出房间回调通知（onRoomUserUpdate:userList:room:），默认关闭
@property (nonatomic, assign) BOOL isUserStatusNotify;

/// 创建默认房间配置
+ (instancetype)defaultConfig;

/// 创建房间配置
- (instancetype)initWithMaxMemberCount:(int)count isUserStatusNotify:(BOOL)notify;

@end


/// 视频配置
@interface ZegoVideoConfig : NSObject

/// 采集分辨率
@property (nonatomic, assign) CGSize captureResolution;

/// 编码分辨率
@property (nonatomic, assign) CGSize encodeResolution;

/// 码率，单位为 bps
@property (nonatomic, assign) int bitrate;

/// 帧率
@property (nonatomic, assign) int fps;

/// 创建默认视频配置(360p, 15fps, 600000bps)
+ (instancetype)defaultConfig;

/// 通过预设枚举值创建视频配置
+ (instancetype)configWithResolution:(ZegoResolution)resolution;

/// 通过预设枚举值创建视频配置
- (instancetype)initWithResolution:(ZegoResolution)resolution;

@end


/// 用户对象
@interface ZegoUser : NSObject

/// 用户 ID，最大128字节的字符串
@property (nonatomic, copy) NSString *userID;

/// 用户名，最大128字节的字符串
@property (nonatomic, copy) NSString *userName;

/// 创建用户对象，userName 与 userID 设为一致
+ (instancetype)userWithUserID:(NSString *)userID;

/// 创建用户对象，userName 与 userID 设为一致
- (instancetype)initWithUserID:(NSString *)userID;

/// 创建用户对象
+ (instancetype)userWithUserID:(NSString *)userID userName:(NSString *)userName;

/// 创建用户对象
- (instancetype)initWithUserID:(NSString *)userID userName:(NSString *)userName;

@end


/// 音视频流对象
@interface ZegoStream : NSObject

/// 用户对象实例
@property (nonatomic, strong) ZegoUser *user;

/// 流 ID，最大256字节的字符串
@property (nonatomic, copy) NSString *streamID;

/// 流附加信息
@property (nonatomic, copy) NSString *extraInfo;

@end


/// 视图对象
@interface ZegoCanvas : NSObject

/// View 对象
@property (nonatomic, strong) ZGView *view;

/// 视图模式，默认为 ZegoViewModeAspectFit
@property (nonatomic, assign) ZegoViewMode viewMode;

/// 背景颜色，格式为 0xRRGGBB，默认为黑色即 0x000000
@property (nonatomic, assign) int backgroundColor;

/// 创建视图，viewMode 默认为 ZegoViewModeAspectFit，背景色默认为黑色
+ (instancetype)canvasWithView:(ZGView *)view;

/// 创建视图，viewMode 默认为 ZegoViewModeAspectFit，背景色默认为黑色
- (instancetype)initWithView:(ZGView *)view;

@end


/// 推流质量对象
@interface ZegoPublishStreamQuality : NSObject

/// 视频采集帧率
@property (nonatomic, assign) double videoCaptureFPS;

/// 视频编码帧率
@property (nonatomic, assign) double videoEncodeFPS;

/// 视频发送帧率
@property (nonatomic, assign) double videoSendFPS;

/// 视频码率
@property (nonatomic, assign) double videoKBPS;

/// 音频采集帧率
@property (nonatomic, assign) double audioCaptureFPS;

/// 音频发送帧率
@property (nonatomic, assign) double audioSendFPS;

/// 音频码率
@property (nonatomic, assign) double audioKBPS;

/// 本端至服务端的延迟，单位为毫秒
@property (nonatomic, assign) int rtt;

/// 丢包率，单位为百分比，0.0 ~ 1.0
@property (nonatomic, assign) double packetLostRate;

/// 推流质量级别
@property (nonatomic, assign) ZegoStreamQualityLevel level;

/// 是否开启硬件编码
@property (nonatomic, assign) BOOL isHardwareEncode;

@end


/// 转推 CDN 信息
@interface ZegoStreamRelayCDNInfo : NSObject

/// 转推至 CDN 的 URL
@property (nonatomic, copy) NSString *URL;

/// 转推状态
@property (nonatomic, assign) ZegoStreamRelayCDNState state;

/// 转推状态变更的原因
@property (nonatomic, assign) ZegoStreamRelayCDNUpdateReason updateReason;

/// 状态发生的时间戳，单位为毫秒
@property (nonatomic, assign) unsigned long long stateTime;

@end


/// 拉流质量对象
@interface ZegoPlayStreamQuality : NSObject

/// 视频接收帧率
@property (nonatomic, assign) double videoRecvFPS;

/// 视频解码帧率
@property (nonatomic, assign) double videoDecodeFPS;

/// 视频渲染帧率
@property (nonatomic, assign) double videoRenderFPS;

/// 视频码率
@property (nonatomic, assign) double videoKBPS;

/// 音频接收帧率
@property (nonatomic, assign) double audioRecvFPS;

/// 音频解码帧率
@property (nonatomic, assign) double audioDecodeFPS;

/// 音频渲染帧率
@property (nonatomic, assign) double audioRenderFPS;

/// 音频码率
@property (nonatomic, assign) double audioKBPS;

/// 服务端至本端的延迟，单位为毫秒
@property (nonatomic, assign) int rtt;

/// 丢包率，单位为百分比，0.0 ~ 1.0
@property (nonatomic, assign) double packetLostRate;

/// 拉流质量等级
@property (nonatomic, assign) ZegoStreamQualityLevel level;

/// 本端接收到数据后到播放的延迟，单位为毫秒
@property (nonatomic, assign) int delay;

/// 是否开启硬件解码
@property (nonatomic, assign) BOOL isHardwareDecode;

@end


/// 设备信息对象
@interface ZegoDeviceInfo : NSObject

/// 设备 ID
@property (nonatomic, copy) NSString *deviceID;

/// 设备名称
@property (nonatomic, copy) NSString *deviceName;

@end


/// 美颜参数对象
@interface ZegoBeautifyOption : NSObject

/// 美颜磨皮的采样步长，取值范围[0,1]。默认 0.2
@property (nonatomic, assign) double polishStep;

/// 美颜美白的亮度参数，取值范围[0,1]，值越大亮度越亮。默认 0.5
@property (nonatomic, assign) double whitenFactor;

/// 美颜锐化参数，取值范围[0,1]，值越大锐化越强。默认 0.1
@property (nonatomic, assign) double sharpenFactor;

/// 创建默认美颜参数对象
+ (instancetype)defaultConfig;

@end


/// 混流音频配置
@interface ZegoMixerAudioConfig : NSObject

/// 音频码率，默认为 48*1000 bit/s，开始混流任务后不能修改
@property (nonatomic, assign) int bitrate;

/// 创建默认混流音频配置，音频码率为 48*1000 bit/s
+ (instancetype)defaultConfig;

@end


/// 混流视频配置
@interface ZegoMixerVideoConfig : NSObject

/// 视频分辨率
@property (nonatomic, assign) CGSize resolution;

/// 视频帧率，开始混流任务后不能修改
@property (nonatomic, assign) int fps;

/// 视频码率
@property (nonatomic, assign) int bitrate;

/// 创建默认混流视频配置，ZegoResolution360x640
+ (instancetype)defaultConfig;

/// 通过预设枚举值创建视频配置
+ (instancetype)configWithResolution:(ZegoResolution)resolution;

/// 通过预设枚举值创建视频配置
- (instancetype)initWithResolution:(ZegoResolution)resolution;

@end


/// 混流输入
@interface ZegoMixerInput : NSObject

/// 混流内容类型
@property (nonatomic, assign) ZegoMixerInputContentType contentType;

/// 流 ID
@property (nonatomic, copy) NSString *streamID;

/// 流的布局
@property (nonatomic, assign) CGRect layout;

/// 创建混流输入对象
- (instancetype)initWithStreamID:(NSString *)streamID contentType:(ZegoMixerInputContentType)contentType layout:(CGRect)layout;

@end


/// 混流输出
@interface ZegoMixerOutput : NSObject

/// 混流输出目标，URL 或者流 ID
@property (nonatomic, copy) NSString *target;

/// 创建混流输出对象
- (instancetype)initWithTarget:(NSString *)target;

@end


/// 水印对象
@interface ZegoWatermark : NSObject

/// 水印图片 URL
@property (nonatomic, copy) NSString *imageURL;

/// 水印图片的大小方位
@property (nonatomic, assign) CGRect layout;

/// 创建水印对象
- (instancetype)initWithImageURL:(NSString *)imageURL layout:(CGRect)layout;

@end


/// 混流任务对象
@interface ZegoMixerTask : NSObject

/// 混流任务ID
@property (nonatomic, copy, readonly) NSString *taskID;

/// 此方法不可用，请使用 `initWithTaskID:`
+ (instancetype)new NS_UNAVAILABLE;

/// 此方法不可用，请使用 `initWithTaskID:`
- (instancetype)init NS_UNAVAILABLE;

/// 通过 TaskID 构造一个混流任务对象
- (instancetype)initWithTaskID:(NSString *)taskID;

/// 设置混流任务对象的音频配置
- (void)setAudioConfig:(ZegoMixerAudioConfig *)audioConfig;

/// 设置混流任务对象的视频配置
- (void)setVideoConfig:(ZegoMixerVideoConfig *)videoConfig;

/// 设置混流任务对象的输入流列表
- (void)setInputList:(NSArray<ZegoMixerInput *> *)inputList;

/// 设置混流任务对象的输出列表
- (void)setOutputList:(NSArray<ZegoMixerOutput *> *)outputList;

/// 设置混流任务对象的水印
- (void)setWatermark:(ZegoWatermark *)watermark;

/// 设置混流任务对象的背景图片
- (void)setBackgroundImageURL:(NSString *)backgroundImageURL;

@end


/// 混流 CDN 详情
@interface ZegoMixerCDNInfo : NSObject

/// rtmp地址列表
@property (nonatomic, strong) NSArray<NSString *> *rtmpList;

/// flv地址列表
@property (nonatomic, strong) NSArray<NSString *> *flvList;

/// hls地址列表
@property (nonatomic, strong) NSArray<NSString *> *hlsList;

@end


/// 开始混流的结果
@interface ZegoMixerStartResult : NSObject

/// 错误码
@property (nonatomic, assign) int errorCode;

@end


/// 收到的消息
@interface ZegoMessageInfo : NSObject

/// 消息内容
@property (nonatomic, copy) NSString *message;

/// 消息的发送时间
@property (nonatomic, assign) unsigned long long sendTime;

/// 消息的发送者
@property (nonatomic, strong) ZegoUser *fromUser;

@end


/// 视频帧的参数对象
@interface ZegoVideoFrameParam : NSObject

/// 视频帧的格式
@property (nonatomic, assign) ZegoVideoFrameFormat format;

/// 每个平面一行字节数（此参数为 int 数组，数组长度为4，RGBA 只需考虑 strides[0]，I420 需考虑 strides[0,1,2]）
@property (nonatomic, assign) int *strides;

/// 视频帧的画面尺寸
@property (nonatomic, assign) CGSize size;

@end


/// 音频帧的参数对象
@interface ZegoAudioFrameParam : NSObject

/// 采样率
@property (nonatomic, assign) int sampleRate;

/// 声道数
@property (nonatomic, assign) int channels;

@end


/// 推流音频配置
@interface ZegoAudioConfig : NSObject

/// 码率
@property (nonatomic, assign) int bitrate;

/// 声道数
@property (nonatomic, assign) int channels;

/// 编码 ID
@property (nonatomic, assign) int codecID;

/// 创建默认音频配置(ZegoAudioConfigPresetLowLatencyStandardQuality)
+ (instancetype)defaultConfig;

/// 通过预设枚举值创建音频配置
+ (instancetype)configWithPreset:(ZegoAudioConfigPreset)preset;

/// 通过预设枚举值创建音频配置
- (instancetype)initWithPreset:(ZegoAudioConfigPreset)preset;

@end


/// 媒体播放器
@interface ZegoMediaPlayer : NSObject

/// 整个文件的播放时长，毫秒
@property (nonatomic, assign, readonly) unsigned long long totalDuration;

/// 当前播放进度，毫秒
@property (nonatomic, assign, readonly) unsigned long long currentProgress;

/// 当前音量，0 ~ 100
@property (nonatomic, assign, readonly) int volume;

/// 播放器当前的播放状态
@property (nonatomic, assign, readonly) ZegoMediaPlayerState currentState;

/// 此方法不可用，请使用 `-[ZegoExpressEngine(MediaPlayer) createMediaPlayer]`
+ (instancetype)new NS_UNAVAILABLE;

/// 此方法不可用，请使用 `-[ZegoExpressEngine(MediaPlayer) createMediaPlayer]`
- (instancetype)init NS_UNAVAILABLE;

/// 设置播放器事件通知回调
- (void)setEventHandler:(nullable id<ZegoMediaPlayerEventHandler>)handler;

/// 设置播放器视频数据回调，希望接收的视频帧数据格式以及数据类型
- (void)setVideoHandler:(nullable id<ZegoMediaPlayerVideoHandler>)handler format:(ZegoVideoFrameFormat)format type:(ZegoVideoBufferType)type;

/// 设置播放器音频数据回调
- (void)setAudioHandler:(nullable id<ZegoMediaPlayerAudioHandler>)handler;

/// 加载资源，可传本地资源的绝对路径或者网络资源的 URL
- (void)loadResource:(NSString *)path callback:(nullable ZegoMediaPlayerLoadResourceCallback)callback;

/// 开始播放（播放前需要先加载资源）
- (void)start;

/// 停止播放
- (void)stop;

/// 暂停播放
- (void)pause;

/// 恢复播放
- (void)resume;

/// 设置指定播放进度，毫秒
- (void)seekTo:(unsigned long long)millisecond callback:(nullable ZegoMediaPlayerSeekToCallback)callback;

/// 设置是否重复播放
- (void)enableRepeat:(BOOL)enable;

/// 设置是否将播放器的声音混入正在推的流中
- (void)enableAux:(BOOL)enable;

/// 是否静默本地播放（若开启了混音入流则推的流中仍然有声音）
- (void)muteLocal:(BOOL)mute;

/// 设置播放器视图
- (void)setPlayerCanvas:(nullable ZegoCanvas *)canvas;

/// 设置播放器音量
- (void)setVolume:(int)volume;

/// 设置播放进度回调间隔
- (void)setProgressInterval:(unsigned long long)millisecond;

@end


NS_ASSUME_NONNULL_END

