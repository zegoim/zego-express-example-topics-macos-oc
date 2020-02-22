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

/// Callback block for updating stream extra information
typedef void(^ZegoPublisherSetStreamExtraInfoCallback)(int errorCode);

/// Callback block for add/remove CDN URL
typedef void(^ZegoPublisherUpdateCDNURLCallback)(int errorCode);

/// Callback block for start mixer task
typedef void(^ZegoMixerStartCallback)(ZegoMixerStartResult *result);

/// Callback block for sending broadcast messages
typedef void(^ZegoIMSendBroadcastMessageCallback)(int errorCode);

/// Callback block for sending custom command
typedef void(^ZegoIMSendCustomCommandCallback)(int errorCode);

/// Callback block for media player loads resources
typedef void(^ZegoMediaPlayerLoadResourceCallback)(int errorCode);

/// Callback block for media player seek to playback progress
typedef void(^ZegoMediaPlayerSeekToCallback)(int errorCode);


/// Application scenario
typedef NS_ENUM(NSUInteger, ZegoScenario) {
    /// General scenario
    ZegoScenarioGeneral = 0,
};


/// Language
typedef NS_ENUM(NSUInteger, ZegoLanguage) {
    /// English
    ZegoLanguageEnglish = 0,
    /// Chinese
    ZegoLanguageChinese = 1,
};


/// Room status
typedef NS_ENUM(NSUInteger, ZegoRoomState) {
    /// Unconnected state, enter this state before logging in and after exiting the room. If there is a steady state abnormality in the process of logging in to the room, such as AppID and AppSign are incorrect, or if the same user name is logged in elsewhere and the local end is KickOut, it will enter this state.
    ZegoRoomStateDisconnected = 0,
    /// The state that the connection is being requested. It will enter this state after successful execution login room function. The display of the application interface is usually performed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting connection status.
    ZegoRoomStateConnecting = 1,
    /// The status that is successfully connected. Entering this status indicates that the login to the room has been successful. The user can receive the callback notification of the user and the stream information in the room.
    ZegoRoomStateConnected = 2,
};


/// Video rendering mode
typedef NS_ENUM(NSUInteger, ZegoViewMode) {
    /// The proportional scaling up, there may be black borders
    ZegoViewModeAspectFit = 0,
    /// The proportional zoom fills the entire View and may be partially cut
    ZegoViewModeAspectFill = 1,
    /// Fill the entire view, the image may be stretched
    ZegoViewModeScaleToFill = 2,
};


/// Mirror mode for previewing or playing the  of the stream
typedef NS_ENUM(NSUInteger, ZegoVideoMirrorMode) {
    /// The mirror image only for previewing locally. This mode is used by default.
    ZegoVideoMirrorModeOnlyPreviewMirror = 0,
    /// Both the video previewed locally and the far end playing the stream will see mirror image.
    ZegoVideoMirrorModeBothMirror = 1,
    /// Both the video previewed locally and the far end playing the stream will not see mirror image.
    ZegoVideoMirrorModeNoMirror = 2,
    /// The mirror image only for far end playing the stream.
    ZegoVideoMirrorModeOnlyPublishMirror = 3,
};


/// Publish stream status
typedef NS_ENUM(NSUInteger, ZegoPublisherState) {
    /// The state is not published, and it is in this state before publishing the stream. If a steady-state exception occurs in the publish process, such as AppID and AppSign are incorrect, or if other users are already publishing the stream, there will be a failure and enter this state.
    ZegoPublisherStateNoPublish = 0,
    /// The state that it is requesting to publish the stream. After the publish stream interface is successfully called, and the application interface is usually displayed using the state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state.
    ZegoPublisherStatePublishRequesting = 1,
    /// The state that the stream is being published, entering the state indicates that the stream has been successfully published, and the user can communicate normally.
    ZegoPublisherStatePublishing = 2,
};


/// Video Resolution
typedef NS_ENUM(NSUInteger, ZegoResolution) {
    /// Set the resolution to 180x320, the default is 15 fps, the code rate is 300,000 bps
    ZegoResolution180x320 = 0,
    /// Set the resolution to 270x480, the default is 15 fps, the code rate is 400,000 bps
    ZegoResolution270x480 = 1,
    /// Set the resolution to 360x640, the default is 15 fps, the code rate is 600,000 bps
    ZegoResolution360x640 = 2,
    /// Set the resolution to 540x960, the default is 15 fps, the code rate is 1200,000 bps
    ZegoResolution540x960 = 3,
    /// Set the resolution to 720x1280, the default is 15 fps, the code rate is 1,500,000 bps
    ZegoResolution720x1280 = 4,
    /// Set the resolution to 1080x1920, the default is 15 fps, the code rate is 3,000,000 bps
    ZegoResolution1080x1920 = 5,
};


/// Event when first frame captured
typedef NS_ENUM(NSUInteger, ZegoPublisherFirstFrameEvent) {
    /// Event when first audio frame captured
    ZegoPublisherFirstFrameEventAudioCaptured = 0,
    /// Event when first video frame captured
    ZegoPublisherFirstFrameEventVideoCaptured = 1,
};


/// Stream quality level
typedef NS_ENUM(NSUInteger, ZegoStreamQualityLevel) {
    /// Excellent
    ZegoStreamQualityLevelExcellent = 0,
    /// Good
    ZegoStreamQualityLevelGood = 1,
    /// Normal
    ZegoStreamQualityLevelMedium = 2,
    /// Bad
    ZegoStreamQualityLevelBad = 3,
    /// Failed
    ZegoStreamQualityLevelDie = 4,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoLatencyMode) {
    /// Normal latency mode
    ZegoLatencyModeNormal = 0,
    /// Low latency mode, not available for RTMP streaming
    ZegoLatencyModeLow = 1,
    /// Normal delay mode, up to 192 kbps
    ZegoLatencyModeNormal2 = 2,
    /// Low latency mode, not available for RTMP streams. CPU overhead is slightly lower than ZEGO_LATENCY_MODE_LOW
    ZegoLatencyModeLow2 = 3,
    /// Low latency mode, not available for RTMP streams. Support WebRTC must use this mode
    ZegoLatencyModeLow3 = 4,
    /// Normal latency mode
    ZegoLatencyModeNormal3 = 5,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoAudioChannelType) {
    /// MONO
    ZegoAudioChannelTypeMono = 0,
    /// STEREO
    ZegoAudioChannelTypeStereo = 1,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoAECMode) {
    /// Aggressive echo cancellation may affect the sound quality slightly, but the echo will be very clean
    ZegoAECModeAggressive = 0,
    /// Moderate echo cancellation, which may slightly affect a little bit of sound, but the residual echo will be less
    ZegoAECModeMedium = 1,
    /// Comfortable echo cancellation, that is, echo cancellation does not affect the sound quality of the sound, and sometimes there may be a little echo, but it will not affect the normal listening.
    ZegoAECModeSoft = 2,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoPlayerState) {
    /// The state of the flow is not played, and it is in this state before the stream is played. If the steady flow anomaly occurs during the playing process, such as AppID and AppSign are incorrect, it will enter this state.
    ZegoPlayerStateNoPlay = 0,
    /// The state that the stream is being requested for playing. After the stream playing interface is successfully called, it will enter the state, and the application interface is usually displayed using this state. If the connection is interrupted due to poor network quality, the SDK will perform an internal retry and will return to the requesting state.
    ZegoPlayerStatePlayRequesting = 1,
    /// The state that the stream is being playing, entering the state indicates that the stream has been successfully played, and the user can communicate normally.
    ZegoPlayerStatePlaying = 2,
};


/// Media event when playing
typedef NS_ENUM(NSUInteger, ZegoPlayerMediaEvent) {
    /// Audio stuck event when playing
    ZegoPlayerMediaEventAudioBreakOccur = 0,
    /// Audio stuck event recovery when playing
    ZegoPlayerMediaEventAudioBreakResume = 1,
    /// Video stuck event when playing
    ZegoPlayerMediaEventVideoBreakOccur = 2,
    /// Video stuck event recovery when playing
    ZegoPlayerMediaEventVideoBreakResume = 3,
};


/// First frame event when playing
typedef NS_ENUM(NSUInteger, ZegoPlayerFirstFrameEvent) {
    /// First audio frame is received when playing the stream
    ZegoPlayerFirstFrameEventAudioRcv = 0,
    /// First video frame is received when playing the stream
    ZegoPlayerFirstFrameEventVideoRcv = 1,
    /// First frame is rendered when playing the stream
    ZegoPlayerFirstFrameEventVideoRender = 2,
};


/// Update type
typedef NS_ENUM(NSUInteger, ZegoUpdateType) {
    /// Add
    ZegoUpdateTypeAdd = 0,
    /// Delete
    ZegoUpdateTypeDelete = 1,
};


/// State of CDN relay
typedef NS_ENUM(NSUInteger, ZegoStreamRelayCDNState) {
    /// The state indicates that there is no CDN relay
    ZegoStreamRelayCDNStateStop = 0,
    /// Entering this status indicates that the CDN relay has been successful
    ZegoStreamRelayCDNStateStart = 1,
    /// The CDN relay is being requested
    ZegoStreamRelayCDNStateRetry = 2,
};


/// Reason for state of CDN relay changed
typedef NS_ENUM(NSUInteger, ZegoStreamRelayCDNUpdateReason) {
    /// No error
    ZegoStreamRelayCDNUpdateReasonNone = 0,
    /// Server error
    ZegoStreamRelayCDNUpdateReasonServerError = 1,
    /// Handshake error
    ZegoStreamRelayCDNUpdateReasonHandshakeFailed = 2,
    /// Access point error
    ZegoStreamRelayCDNUpdateReasonAccessPointError = 3,
    /// Stream create failure
    ZegoStreamRelayCDNUpdateReasonCreateStreamFailed = 4,
    /// Bad name
    ZegoStreamRelayCDNUpdateReasonBadName = 5,
    /// CDN server actively disconnected
    ZegoStreamRelayCDNUpdateReasonCDNServerDisconnected = 6,
    /// Active disconnect
    ZegoStreamRelayCDNUpdateReasonDisconnected = 7,
};


/// Beauty feature
typedef NS_OPTIONS(NSUInteger, ZegoBeautifyFeature) {
    /// No beautifying
    ZegoBeautifyFeatureNone = 0,
    /// Polish
    ZegoBeautifyFeaturePolish = 1 << 0,
    /// Sharpen
    ZegoBeautifyFeatureWhiten = 1 << 1,
    /// Skin whiten
    ZegoBeautifyFeatureSkinWhiten = 1 << 2,
    /// Whiten
    ZegoBeautifyFeatureSharpen = 1 << 3,
};


/// Remote device status
typedef NS_ENUM(NSUInteger, ZegoRemoteDeviceState) {
    /// Device on
    ZegoRemoteDeviceStateOpen = 0,
    /// General device error
    ZegoRemoteDeviceStateGenericError = 1,
    /// Invalid device ID
    ZegoRemoteDeviceStateInvalidID = 2,
    /// No permission
    ZegoRemoteDeviceStateNoAuthorization = 3,
    /// Captured frame rate is 0
    ZegoRemoteDeviceStateZeroFPS = 4,
    /// The device is occupied
    ZegoRemoteDeviceStateInUseByOther = 5,
    /// The device is not plugged in or unplugged
    ZegoRemoteDeviceStateUnplugged = 6,
    /// The system needs to be restarted
    ZegoRemoteDeviceStateRebootRequired = 7,
    /// System media services stop, such as under the iOS platform, when the system detects that the current pressure is huge (such as playing a lot of animation), it is possible to disable all media related services.
    ZegoRemoteDeviceStateSystemMediaServicesLost = 8,
    /// Capturing disabled
    ZegoRemoteDeviceStateDisable = 9,
    /// The remote device is muted
    ZegoRemoteDeviceStateMute = 10,
    /// The device is interrupted, such as a phone call interruption, etc.
    ZegoRemoteDeviceStateInterruption = 11,
    /// User app retreats to the background
    ZegoRemoteDeviceStateInBackground = 12,
    /// There are multiple apps at the same time in the foreground, such as the iPad app split screen, the system will prohibit all apps from using the camera.
    ZegoRemoteDeviceStateMultiForegroundApp = 13,
    /// The system is under high load pressure and may cause abnormal equipment.
    ZegoRemoteDeviceStateBySystemPressure = 14,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoAudioDeviceType) {
    /// 
    ZegoAudioDeviceTypeInput = 0,
    /// 
    ZegoAudioDeviceTypeOutput = 1,
};


/// Mix stream content type
typedef NS_ENUM(NSUInteger, ZegoMixerInputContentType) {
    /// Mix stream for audio only
    ZegoMixerInputContentTypeAudio = 0,
    /// Mix stream for both audio and video
    ZegoMixerInputContentTypeVideo = 1,
};


/// Capture pipline scale mode
typedef NS_ENUM(NSUInteger, ZegoCapturePipelineScaleMode) {
    /// Zoom immediately after acquisition, default
    ZegoCapturePipelineScaleModePre = 0,
    /// Scaling while encoding
    ZegoCapturePipelineScaleModePost = 1,
};


/// Video frame format
typedef NS_ENUM(NSUInteger, ZegoVideoFrameFormat) {
    /// Unknown format, will take platform default
    ZegoVideoFrameFormatUnknown = 0,
    /// I420 (YUV420Planar) format
    ZegoVideoFrameFormatI420 = 1,
    /// NV12 (YUV420SemiPlanar) format
    ZegoVideoFrameFormatNV12 = 2,
    /// NV32 (YUV420SemiPlanar) format
    ZegoVideoFrameFormatNV21 = 3,
    /// BGRA32 format
    ZegoVideoFrameFormatBGRA32 = 4,
    /// RGBA32 format
    ZegoVideoFrameFormatRGBA32 = 5,
    /// ARGB32 format
    ZegoVideoFrameFormatARGB32 = 6,
    /// ABGR32 format
    ZegoVideoFrameFormatABGR32 = 7,
    /// I422 (YUV422Planar) format
    ZegoVideoFrameFormatI422 = 8,
};


/// Video buffer type
typedef NS_ENUM(NSUInteger, ZegoVideoBufferType) {
    /// Raw data type video frame
    ZegoVideoBufferTypeUnknown = 0,
    /// Raw data type video frame
    ZegoVideoBufferTypeRawData = 1,
    /// Texture 2D type video frame
    ZegoVideoBufferTypeGLTexture2D = 3,
    /// CVPixelBuffer type video frame
    ZegoVideoBufferTypeCVPixelBuffer = 4,
};


/// Video frame format series
typedef NS_ENUM(NSUInteger, ZegoVideoFrameFormatSeries) {
    /// RGB series
    ZegoVideoFrameFormatSeriesRGB = 0,
    /// YUV series
    ZegoVideoFrameFormatSeriesYUV = 1,
};


/// 
typedef NS_ENUM(NSUInteger, ZegoVideoFlipMode) {
    /// No flip
    ZegoVideoFlipModeNone = 0,
    /// X-axis flip
    ZegoVideoFlipModeX = 1,
};


/// Audio Config Preset
typedef NS_ENUM(NSUInteger, ZegoAudioConfigPreset) {
    /// low-latency-basic-quality
    ZegoAudioConfigPresetLowLatencyBasicQuality = 0,
    /// low-latency-standard-quality
    ZegoAudioConfigPresetLowLatencyStandardQuality = 1,
    /// low-latency-standard-quality-stereo
    ZegoAudioConfigPresetLowLatencyStandardQualityStereo = 2,
    /// low-latency-high-quality
    ZegoAudioConfigPresetLowLatencyHighQuality = 3,
    /// low-latency-high-quality-stereo
    ZegoAudioConfigPresetLowLatencyHighQualityStereo = 4,
    /// normal-latency-standard-quality
    ZegoAudioConfigPresetNormalLatencyStandardQuality = 5,
    /// normal-latency-standard-quality-stereo
    ZegoAudioConfigPresetNormalLatencyStandardQualityStereo = 6,
    /// normal-latency-high-quality
    ZegoAudioConfigPresetNormalLatencyHighQuality = 7,
    /// normal-latency-high-quality-stereo
    ZegoAudioConfigPresetNormalLatencyHighQualityStereo = 8,
};


/// Player state
typedef NS_ENUM(NSUInteger, ZegoMediaPlayerState) {
    /// Not playing
    ZegoMediaPlayerStateNoPlay = 0,
    /// Playing
    ZegoMediaPlayerStatePlaying = 1,
    /// Pausing
    ZegoMediaPlayerStatePausing = 2,
    /// End of play
    ZegoMediaPlayerStatePlayEnded = 3,
};


/// Player network event
typedef NS_ENUM(NSUInteger, ZegoMediaPlayerNetworkEvent) {
    /// Network resources are not playing well, and start trying to cache data
    ZegoMediaPlayerNetworkEventBufferBegin = 0,
    /// Network resources can be played smoothly
    ZegoMediaPlayerNetworkEventBufferEnded = 1,
};


/// Log config
@interface ZegoLogConfig : NSObject

/// The log file path. The default path is [NSCachesDirectory]/ZegoLogs/
@property (nonatomic, copy) NSString *logPath;

/// The maximum log file size (Bytes).  The default maximum size is 5MB (5 * 1024 * 1024 Bytes)
@property (nonatomic, assign) unsigned long long logSize;

@end


/// Custom video capture config
@interface ZegoCustomVideoCaptureConfig : NSObject

/// External capture video buffer type
@property (nonatomic, assign) ZegoVideoBufferType bufferType;

@end


/// Custom video render config
@interface ZegoCustomVideoRenderConfig : NSObject

/// External render video buffer type
@property (nonatomic, assign) ZegoVideoBufferType bufferType;

/// External render video frame format series
@property (nonatomic, assign) ZegoVideoFrameFormatSeries frameFormatSeries;

/// Whether enable internal render while custom video render
@property (nonatomic, assign) BOOL enableEngineRender;

@end


/// Advanced engine configuration
@interface ZegoEngineConfig : NSObject

/// Set the log file path and the maximum log file size (Bytes). The default path is [NSCachesDirectory]/ZegoLogs/, default maximum size is 5MB
@property (nonatomic, strong, nullable) ZegoLogConfig *logConfig;

/// Custom video capture config, if not set, custom video capture config is not enabled by default
@property (nonatomic, strong, nullable) ZegoCustomVideoCaptureConfig *customVideoCaptureConfig;

/// Custom video render config, if not set, custom video render config is not enabled by default
@property (nonatomic, strong, nullable) ZegoCustomVideoRenderConfig *customVideoRenderConfig;

/// Advanced config, if not set, advanced config is not enabled by default
@property (nonatomic, copy, nullable) NSDictionary<NSString *, NSString *> *advancedConfig;

@end


/// Advanced room configuration
@interface ZegoRoomConfig : NSObject

/// The maximum number of users in the room, the default is unlimited
@property (nonatomic, assign) unsigned int maxMemberCount;

/// Whether to enable the user in and out of the room callback notification (onRoomUserUpdate:userList:room:), the default is off
@property (nonatomic, assign) BOOL isUserStatusNotify;

/// Create a default room configuration
+ (instancetype)defaultConfig;

/// Create a room configuration
- (instancetype)initWithMaxMemberCount:(int)count isUserStatusNotify:(BOOL)notify;

@end


/// Video configuration
@interface ZegoVideoConfig : NSObject

/// Captured video resolution
@property (nonatomic, assign) CGSize captureResolution;

/// Encoded video resolution
@property (nonatomic, assign) CGSize encodeResolution;

/// Bit rate in bps
@property (nonatomic, assign) int bitrate;

/// Frame rate in fps
@property (nonatomic, assign) int fps;

/// Create a default video configuration (360p, 15fps, 600000bps)
+ (instancetype)defaultConfig;

/// Create a video configuration with preset enumeration values
+ (instancetype)configWithResolution:(ZegoResolution)resolution;

/// Create a video configuration with preset enumeration values
- (instancetype)initWithResolution:(ZegoResolution)resolution;

@end


/// User
@interface ZegoUser : NSObject

/// User ID, a string with a maximum length of 128 bytes or less
@property (nonatomic, copy) NSString *userID;

/// User Name, a string with a maximum length of 128 bytes or less
@property (nonatomic, copy) NSString *userName;

/// Create a ZegoUser object, userName and userID are set to match
+ (instancetype)userWithUserID:(NSString *)userID;

/// Create a ZegoUser object, userName and userID are set to match
- (instancetype)initWithUserID:(NSString *)userID;

/// Create a ZegoUser object
+ (instancetype)userWithUserID:(NSString *)userID userName:(NSString *)userName;

/// Create a ZegoUser object
- (instancetype)initWithUserID:(NSString *)userID userName:(NSString *)userName;

@end


/// Stream
@interface ZegoStream : NSObject

/// User object instance
@property (nonatomic, strong) ZegoUser *user;

/// Stream ID,a string with a maximum length of no more than 128 bytes
@property (nonatomic, copy) NSString *streamID;

/// Stream extra info
@property (nonatomic, copy) NSString *extraInfo;

@end


/// View object
@interface ZegoCanvas : NSObject

/// View
@property (nonatomic, strong) ZGView *view;

/// View mode, default is ZegoViewModeAspectFit
@property (nonatomic, assign) ZegoViewMode viewMode;

/// Background color, the format is 0xRRGGBB, default is black, which is 0x000000
@property (nonatomic, assign) int backgroundColor;

/// Create a ZegoCanvas, default viewMode is ZegoViewModeAspectFit, default background color is black
+ (instancetype)canvasWithView:(ZGView *)view;

/// Create a ZegoCanvas, default viewMode is ZegoViewModeAspectFit, default background color is black
- (instancetype)initWithView:(ZGView *)view;

@end


/// Published stream quality information
@interface ZegoPublishStreamQuality : NSObject

/// Video capture frame rate
@property (nonatomic, assign) double videoCaptureFPS;

/// Video encoding frame rate
@property (nonatomic, assign) double videoEncodeFPS;

/// Video transmission frame rate
@property (nonatomic, assign) double videoSendFPS;

/// Video bit rate
@property (nonatomic, assign) double videoKBPS;

/// Audio capture frame rate
@property (nonatomic, assign) double audioCaptureFPS;

/// Audio transmission frame rate
@property (nonatomic, assign) double audioSendFPS;

/// Audio bit rate
@property (nonatomic, assign) double audioKBPS;

/// Local to server delay, in milliseconds
@property (nonatomic, assign) int rtt;

/// Packet loss rate, in percentage, 0.0 ~ 1.0
@property (nonatomic, assign) double packetLostRate;

/// Published stream quality level
@property (nonatomic, assign) ZegoStreamQualityLevel level;

/// Whether to enable hardware encoding
@property (nonatomic, assign) BOOL isHardwareEncode;

@end


/// Relay to CDN execution information
@interface ZegoStreamRelayCDNInfo : NSObject

/// URL relayed to CDN
@property (nonatomic, copy) NSString *URL;

/// Status for relaying
@property (nonatomic, assign) ZegoStreamRelayCDNState state;

/// Reason for relay status change
@property (nonatomic, assign) ZegoStreamRelayCDNUpdateReason updateReason;

/// The timestamp when the state changed, in milliseconds
@property (nonatomic, assign) unsigned long long stateTime;

@end


/// Played stream quality information
@interface ZegoPlayStreamQuality : NSObject

/// Video reception frame rate
@property (nonatomic, assign) double videoRecvFPS;

/// Video decoding frame rate
@property (nonatomic, assign) double videoDecodeFPS;

/// Video rendering frame rate
@property (nonatomic, assign) double videoRenderFPS;

/// Video bit rate
@property (nonatomic, assign) double videoKBPS;

/// Audio reception frame rate
@property (nonatomic, assign) double audioRecvFPS;

/// Audio decoding frame rate
@property (nonatomic, assign) double audioDecodeFPS;

/// Audio rendering frame rate
@property (nonatomic, assign) double audioRenderFPS;

/// Audio bit rate
@property (nonatomic, assign) double audioKBPS;

/// Server to local delay, in milliseconds
@property (nonatomic, assign) int rtt;

/// Packet loss rate, in percentage, 0.0 ~ 1.0
@property (nonatomic, assign) double packetLostRate;

/// Pull flow quality level
@property (nonatomic, assign) ZegoStreamQualityLevel level;

/// Delay after the data is received by the local end, in milliseconds
@property (nonatomic, assign) int delay;

/// Whether to enable hardware decoding
@property (nonatomic, assign) BOOL isHardwareDecode;

@end


/// Device
@interface ZegoDeviceInfo : NSObject

/// Device ID
@property (nonatomic, copy) NSString *deviceID;

/// Device name
@property (nonatomic, copy) NSString *deviceName;

@end


/// Beauty configuration options
@interface ZegoBeautifyOption : NSObject

/// The sample step size of beauty peeling, the value range is [0,1]. Default 0.2
@property (nonatomic, assign) double polishStep;

/// Brightness parameter for beauty and whitening, ranging from [0,1]. The larger the value, the brighter the brightness. Default 0.5
@property (nonatomic, assign) double whitenFactor;

/// Beauty sharpening parameter, value range [0,1], the larger the value, the stronger the sharpening. Default 0.1
@property (nonatomic, assign) double sharpenFactor;

/// Create a default beautify option configuration
+ (instancetype)defaultConfig;

@end


/// Mix stream audio config object
@interface ZegoMixerAudioConfig : NSObject

/// Audio bitrate, default is 48 * 1000 bit/s, cannot be modified after starting a mixer task
@property (nonatomic, assign) int bitrate;

/// Create a default mix stream audio configuration, audio bitrate is  48 * 1000 bit/s
+ (instancetype)defaultConfig;

@end


/// Mix stream video config object
@interface ZegoMixerVideoConfig : NSObject

/// Video resolution
@property (nonatomic, assign) CGSize resolution;

/// Video FPS, cannot be modified after starting a mixer task
@property (nonatomic, assign) int fps;

/// Video bitrate
@property (nonatomic, assign) int bitrate;

/// Create a default mix stream video configuration, ZegoResolution360x640
+ (instancetype)defaultConfig;

/// Create a video configuration with preset enumeration values
+ (instancetype)configWithResolution:(ZegoResolution)resolution;

/// Create a video configuration with preset enumeration values
- (instancetype)initWithResolution:(ZegoResolution)resolution;

@end


/// Mix stream input object
@interface ZegoMixerInput : NSObject

/// Mix stream content type
@property (nonatomic, assign) ZegoMixerInputContentType contentType;

/// Stream ID
@property (nonatomic, copy) NSString *streamID;

/// Layout of the stream
@property (nonatomic, assign) CGRect layout;

/// Create a mix stream input object
- (instancetype)initWithStreamID:(NSString *)streamID contentType:(ZegoMixerInputContentType)contentType layout:(CGRect)layout;

@end


/// Mix stream output object
@interface ZegoMixerOutput : NSObject

/// Mix stream output target, URL or stream ID
@property (nonatomic, copy) NSString *target;

/// Create a mix stream output object
- (instancetype)initWithTarget:(NSString *)target;

@end


/// Watermark object
@interface ZegoWatermark : NSObject

/// Watermark image URL
@property (nonatomic, copy) NSString *imageURL;

/// Watermark image layout
@property (nonatomic, assign) CGRect layout;

/// Create a watermark object
- (instancetype)initWithImageURL:(NSString *)imageURL layout:(CGRect)layout;

@end


/// Mix stream task object
@interface ZegoMixerTask : NSObject

/// Mixer task ID
@property (nonatomic, copy, readonly) NSString *taskID;

/// This method is unavaialble. Please use `initWithTaskID:` instead.
+ (instancetype)new NS_UNAVAILABLE;

/// This method is unavaialble. Please use `initWithTaskID:` instead.
- (instancetype)init NS_UNAVAILABLE;

/// Create a mix stream task object with TaskID
- (instancetype)initWithTaskID:(NSString *)taskID;

/// Set the audio configuration of the mix stream task object
- (void)setAudioConfig:(ZegoMixerAudioConfig *)audioConfig;

/// Set the video configuration of the mix stream task object
- (void)setVideoConfig:(ZegoMixerVideoConfig *)videoConfig;

/// Set the input stream list for the mix stream task object
- (void)setInputList:(NSArray<ZegoMixerInput *> *)inputList;

/// Set the output list of the mix stream task object
- (void)setOutputList:(NSArray<ZegoMixerOutput *> *)outputList;

/// Set the watermark of the mix stream task object
- (void)setWatermark:(ZegoWatermark *)watermark;

/// Set the background image of the mix stream task object
- (void)setBackgroundImageURL:(NSString *)backgroundImageURL;

@end


/// Mix Stream CDN information
@interface ZegoMixerCDNInfo : NSObject

/// rtmp URL list
@property (nonatomic, strong) NSArray<NSString *> *rtmpList;

/// flv URL list
@property (nonatomic, strong) NSArray<NSString *> *flvList;

/// hls URL list
@property (nonatomic, strong) NSArray<NSString *> *hlsList;

@end


/// Start mix stream results
@interface ZegoMixerStartResult : NSObject

/// Error code
@property (nonatomic, assign) int errorCode;

@end


/// Received message
@interface ZegoMessageInfo : NSObject

/// Message content
@property (nonatomic, copy) NSString *message;

/// Message send time
@property (nonatomic, assign) unsigned long long sendTime;

/// Message sender
@property (nonatomic, strong) ZegoUser *fromUser;

@end


/// Parameter object for video frame
@interface ZegoVideoFrameParam : NSObject

/// Video frame format
@property (nonatomic, assign) ZegoVideoFrameFormat format;

/// Number of bytes per line (this parameter is an int array, the array length is 4,  RGBA only needs to consider strides [0], I420 needs to consider strides [0,1,2])
@property (nonatomic, assign) int *strides;

/// Video frame size
@property (nonatomic, assign) CGSize size;

@end


/// Parameter object for audio frame
@interface ZegoAudioFrameParam : NSObject

/// Sampling Rate
@property (nonatomic, assign) int sampleRate;

/// Number of channels
@property (nonatomic, assign) int channels;

@end


/// Audio configuration
@interface ZegoAudioConfig : NSObject

/// Bitrate
@property (nonatomic, assign) int bitrate;

/// Channel count
@property (nonatomic, assign) int channels;

/// Codec ID
@property (nonatomic, assign) int codecID;

/// Create a default audio configuration (ZegoAudioConfigPresetLowLatencyStandardQuality)
+ (instancetype)defaultConfig;

/// Create a audio configuration with preset enumeration values
+ (instancetype)configWithPreset:(ZegoAudioConfigPreset)preset;

/// Create a audio configuration with preset enumeration values
- (instancetype)initWithPreset:(ZegoAudioConfigPreset)preset;

@end


/// Media Player
@interface ZegoMediaPlayer : NSObject

/// The duration of the entire file, in milliseconds
@property (nonatomic, assign, readonly) unsigned long long totalDuration;

/// Current playback progress, milliseconds
@property (nonatomic, assign, readonly) unsigned long long currentProgress;

/// Current volume, 0 ~ 100
@property (nonatomic, assign, readonly) int volume;

/// Player's current playback status
@property (nonatomic, assign, readonly) ZegoMediaPlayerState currentState;

/// This method is unavaialble. Please use `-[ZegoExpressEngine(MediaPlayer) createMediaPlayer]` instead.
+ (instancetype)new NS_UNAVAILABLE;

/// This method is unavaialble. Please use `-[ZegoExpressEngine(MediaPlayer) createMediaPlayer]` instead.
- (instancetype)init NS_UNAVAILABLE;

/// Set player event callback handler
- (void)setEventHandler:(nullable id<ZegoMediaPlayerEventHandler>)handler;

/// Set the player video data callback handler, the video frame data format and data type you want to receive
- (void)setVideoHandler:(nullable id<ZegoMediaPlayerVideoHandler>)handler format:(ZegoVideoFrameFormat)format type:(ZegoVideoBufferType)type;

/// Set player audio data callback handler
- (void)setAudioHandler:(nullable id<ZegoMediaPlayerAudioHandler>)handler;

/// Load the resource, you can pass the absolute path of the local resource or the URL of the network resource
- (void)loadResource:(NSString *)path callback:(nullable ZegoMediaPlayerLoadResourceCallback)callback;

/// Start playing (requires loading resources before playing)
- (void)start;

/// Stop play
- (void)stop;

/// Pause playback
- (void)pause;

/// Resume playback
- (void)resume;

/// Sets the specified playback progress in milliseconds
- (void)seekTo:(unsigned long long)millisecond callback:(nullable ZegoMediaPlayerSeekToCallback)callback;

/// Set whether to repeat playback
- (void)enableRepeat:(BOOL)enable;

/// Set whether to mix the player's sound into the stream being publish
- (void)enableAux:(BOOL)enable;

/// Whether to play locally silently (if aux is enabled, there will still be sound in the publish stream)
- (void)muteLocal:(BOOL)mute;

/// Set player view
- (void)setPlayerCanvas:(nullable ZegoCanvas *)canvas;

/// Set player volume
- (void)setVolume:(int)volume;

/// Set playback progress callback interval
- (void)setProgressInterval:(unsigned long long)millisecond;

@end


NS_ASSUME_NONNULL_END

