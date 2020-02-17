//
//  ZegoExpressEngine+Device.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Device)

/// 开/关麦克风
/// @discussion 此接口用于控制是否使用采集到的音频数据，关闭麦克风即采集到数据后就丢弃，此时仍然会占用麦克风
/// @param mute 是否开启麦克风，YES 表示关闭麦克风；NO 表示开启麦克风
- (void)muteMicrophone:(BOOL)mute;

/// 开/关音频输出至设备
/// @discussion 关闭后SDK将不会再传递音频数据给输出设备，以达到静音的效果
/// @param mute 是否开启音频输出到设备，YES 表示关闭音频输出；NO 表示开启音频输出
- (void)muteAudioOutput:(BOOL)mute;

#if TARGET_OS_OSX
/// 选择使用某个音频设备
/// @discussion 只适用于 macOS
/// @param deviceID 通过 getAudioDeviceList: 获取的某个设备的 ID
/// @param deviceType 音频设备类型
- (void)useAudioDevice:(NSString *)deviceID type:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_OSX
/// 获取音频设备列表
/// @discussion 只适用于 macOS
/// @param deviceType 音频设备类型
/// @return 音频设备列表
- (NSArray<ZegoDeviceInfo *> *)getAudioDeviceList:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_IPHONE
/// 开/关音频采集设备
/// @discussion 此接口用于控制是否释放音频采集设备，关闭音频采集设备，则 SDK 不会再占用音频设备，当然如果此时正在推流，也没有音频数据。
/// @param enable 是否使能音频采集设备，YES 表示开启音频采集设备，NO 表示关闭音频采集设备
- (void)enableAudioCaptureDevice:(BOOL)enable;
#endif

/// 开/关摄像头
/// @discussion 此接口用于控制是否启动摄像头的采集，关闭摄像头后，将不会进行视频采集，此时推流也将没有视频数据
/// @param enable 是否打开摄像头，NO 表示关闭摄像头；YES 表示开启摄像头
- (void)enableCamera:(BOOL)enable;

#if TARGET_OS_IPHONE
/// 切换前后摄像头
/// @discussion 此接口用于控制使用前摄像头或者后摄像头
/// @param enable 是否采用前置摄像头，NO 表示使用后置摄像头；YES 表示使用前置摄像头
- (void)useFrontCamera:(BOOL)enable;
#endif

#if TARGET_OS_OSX
/// 选择使用某个视频设备
/// @discussion 只适用于 macOS
/// @param deviceID 通过 getVideoDeviceList: 获取的某个设备的 ID
- (void)useVideoDevice:(NSString *)deviceID;
#endif

#if TARGET_OS_OSX
/// 获取视频设备列表
/// @discussion 只适用于 macOS
/// @return 视频设备列表
- (NSArray<ZegoDeviceInfo *> *)getVideoDeviceList;
#endif

/// 启动声浪监控
- (void)startSoundLevelMonitor;

/// 停止声浪监控
- (void)stopSoundLevelMonitor;

/// 启动音频频谱监控
- (void)startAudioSpectrumMonitor;

/// 停止音频频谱监控
- (void)stopAudioSpectrumMonitor;

@end

NS_ASSUME_NONNULL_END
