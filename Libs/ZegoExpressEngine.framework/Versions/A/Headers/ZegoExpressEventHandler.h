//
//  ZegoExpressEventHandler.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressDefines.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - Zego Event Handler

@protocol ZegoEventHandler <NSObject>

@optional

/// 调试错误信息回调
/// @discussion 调用 SDK 接口出现异常时，会通过该回调提示详细的异常信息，该回调受 setDebugVerbose:language: 接口控制。
/// @param errorCode 错误码，详情请参考常用错误码文档
/// @param funcName 接口名
/// @param info 错误的详细信息
- (void)onDebugError:(int)errorCode funcName:(NSString *)funcName info:(NSString *)info;

#pragma mark Room Callback

/// 房间状态变化回调
/// @discussion 当房间的连接状态发生变化时将触发此回调，并告知发生变化的原因。
/// @param state 变化后的的房间状态
/// @param errorCode 错误码，详情请参考常用错误码文档
/// @param roomID 房间 ID
- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode room:(NSString *)roomID;

/// 房间内用户进出通知回调
/// @discussion 当有用户进入/退出房间时将触发此回调，并告知当前房间内存在的用户的列表；注意，只有在登录房间时传的 ZegoRoomConfig 中的 isUserStatusNotify 参数为 YES 时才会触发这个回调
/// @param updateType 更新类型（添加/删除）
/// @param userList 当前房间内的用户列表
/// @param roomID 房间 ID
- (void)onRoomUserUpdate:(ZegoUpdateType)updateType userList:(NSArray<ZegoUser *> *)userList room:(NSString *)roomID;

/// 房间内流更新回调
/// @discussion 用户首次登录房间时会接收到房间内存在的所有流列表；后续当房间内新增/删除流时将触发此回调通知变更的流列表。
/// @param updateType 更新类型（添加/删除）
/// @param streamList 更新的流列表
/// @param roomID 房间 ID
- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList room:(NSString *)roomID;

/// 房间内流附加信息更新通知
/// @discussion 当房间内有其他推流的用户更新了流的附加信息时，本端会收到该回调
/// @param streamList 流附加信息更新的流列表
/// @param roomID 房间 ID
- (void)onRoomStreamExtraInfoUpdate:(NSArray<ZegoStream *> *)streamList room:(NSString *)roomID;

#pragma mark Publisher Callback

/// 推流状态回调
/// @discussion 在推流成功后，可以通过该回调接口获取推流状态变更的通知。
/// @param state 推流状态
/// @param errorCode 推流状态变更对应的错误码。请参考常见错误码文档。
/// @param streamID 推流的流 ID
- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode stream:(NSString *)streamID;

/// 推流质量回调
/// @discussion 推流成功后每3秒会收到此回调，通过该回调可以获取推送的音视频流的采集帧率，码率，RTT，丢包率等质量数据，实时监控推送流的健康情况。
/// @param quality 推流质量，包含了音视频帧率、码率、分辨率，RTT等值
/// @param streamID 流 ID
- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality stream:(NSString *)streamID;

/// 推流端采集首帧回调
/// @discussion 调用推流接口成功后，SDK 采集到第一帧数据时会收到此回调，包含了音频/视频的采集首帧通知。
/// @param event 推流端采集到首帧时触发的事件，包含音频采集首帧和视频采集首帧事件。
- (void)onPublisherRecvFirstFrameEvent:(ZegoPublisherFirstFrameEvent)event;

/// 采集视频大小变更回调
/// @discussion 推流成功后，在推流中途如果有改变视频采集分辨率发生变化将会收到此回调。
/// @param size 视频采集分辨率
- (void)onPublisherVideoSizeChanged:(CGSize)size;

/// 添加/删除转推CDN地址状态回调
/// @discussion 在 ZEGO 实时音视频云将音视频流转推到 CDN 后，如果 CDN 转推状态发生变化，例如出现转推停止或转推重试，将会收到此回调。
/// @param infoList 当前 CDN 正在转推的信息列表
/// @param streamID 流 ID
- (void)onPublisherRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList stream:(NSString *)streamID;

#pragma mark Player Callback

/// 拉流状态变更回调
/// @discussion 在拉流成功后，可以通过该回调接口获取拉流状态变更的通知。
/// @param state 拉流状态
/// @param errorCode 错误码
/// @param streamID 流 ID
- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode stream:(NSString *)streamID;

/// 拉流质量回调
/// @discussion 拉流成功后每3秒会收到此回调，通过该回调可以获取拉取的音视频流的帧率，码率，RTT，丢包率等质量数据，实时监控拉取流的健康情况。
/// @param quality 拉流质量
/// @param streamID 流 ID
- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality stream:(NSString *)streamID;

/// 拉流媒体事件回调
/// @discussion 当拉流发生音视频卡顿以及恢复等事件发生时会触发此回调。
/// @param event 拉流媒体事件枚举
/// @param streamID 流 ID
- (void)onPlayerMediaEvent:(ZegoPlayerMediaEvent)event stream:(NSString *)streamID;

/// 拉流首帧回调
/// @discussion 调用推流接口成功后，当拉取到音频首帧、视频首帧以及视频首帧被渲染都会触发此回调。
/// @param event 拉流时收到的具体首帧事件
/// @param streamID 流 ID
- (void)onPlayerRecvFirstFrameEvent:(ZegoPlayerFirstFrameEvent)event stream:(NSString *)streamID;

/// 拉流分辨率变更通知
/// @discussion 拉流成功后，在拉流中途如果有视频分辨率发生变化将会收到此回调，用户可根据流的最终分辨率调整显示。
/// @param size 视频分辨率
/// @param streamID 流 ID
- (void)onPlayerVideoSizeChanged:(CGSize)size stream:(NSString *)streamID;

/// 收到远端流的 SEI 内容
/// @discussion 拉流成功后，当远端流调用 "-sendSEI:" 后，本端会收到此回调
/// @param data SEI 内容
/// @param streamID 流 ID
- (void)onPlayerRecvSEI:(NSData *)data stream:(NSString *)streamID;

#pragma mark Mixer Callback

/// 混流转推 CDN 状态更新通知
/// @param infoList 当前 CDN 正在混流的信息列表
/// @param taskID 混流任务 ID
- (void)onMixerRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList taskID:(NSString *)taskID;

#pragma mark Device Callback

#if TARGET_OS_OSX
/// 音频设备状态变更事件
/// @discussion 只适用于 macOS；监测到系统中有音频设备添加或移除时，会触发此回调。通过监听此回调，用户可在必要的时候更新使用特定设备进行声音采集或输出。
/// @param deviceInfo 音频设备信息
/// @param updateType 更新类型（添加/删除）
/// @param deviceType 音频设备类型
- (void)onAudioDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType deviceType:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_OSX
/// 视频设备状态变更事件
/// @discussion 只适用于 macOS；监测到系统中有视频设备添加或移除时，会触发此回调。通过监听此回调，用户可在必要的时候更新使用特定设备进行视频采集。
/// @param deviceInfo 视频设备信息
/// @param updateType 更新类型（添加/删除）
- (void)onVideoDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType;
#endif

/// 本地采集音频声浪回调
/// @param soundLevel 本地采集的声浪值，取值范围为 0.0~100.0
- (void)onCapturedSoundLevelUpdate:(NSNumber *)soundLevel;

/// 远端音频声浪回调
/// @param soundLevels 远端的声浪键值对，key 为流 ID，value 为对应的流的声浪值
- (void)onRemoteSoundLevelUpdate:(NSDictionary<NSString *, NSNumber *> *)soundLevels;

/// 本地采集音频频谱回调
/// @param audioSpectrum 本地采集的音频频谱值数组，频谱值范围为 [0-2^30]  
- (void)onCapturedAudioSpectrumUpdate:(NSArray<NSNumber *> *)audioSpectrum;

/// 远端拉流音频频谱回调
/// @param audioSpectrums 远端音频频谱键值对，key 是流 ID，value 为对应的流的音频频谱值数组，频谱值范围为 [0-2^30]  
- (void)onRemoteAudioSpectrumUpdate:(NSDictionary<NSString *, NSArray<NSNumber *> *> *)audioSpectrums;

/// 设备异常通知
/// @discussion 当本地设备读写出现异常时会触发此回调。
/// @param errorCode 错误码
/// @param deviceName 设备名称
- (void)onDeviceError:(int)errorCode deviceName:(NSString *)deviceName;

/// 远端摄像头设备状态通知
/// @discussion 远端摄像头设备状态发生变更时，例如开关摄像头等，通过监听此回调，能够获取远端摄像头相关的事件，可以用于提示用户可能导致视频异常的情况。
/// @param state 远端摄像头状态
/// @param streamID 流 ID
- (void)onRemoteCameraStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)streamID;

/// 远端麦克风设备状态通知
/// @discussion 远端麦克风设备状态发生变更时，例如开关麦克风等，通过监听此回调，能够获取远端麦克风相关的事件，可以用于提示用户可能导致音频异常的情况。
/// @param state 远端麦克风状态
/// @param streamID 流 ID
- (void)onRemoteMicStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)streamID;

#pragma mark IM Callback

/// 接收房间广播消息通知
/// @param messageInfoList 收到的消息列表
/// @param roomID 房间 ID
- (void)onIMRecvBroadcastMessage:(NSArray<ZegoMessageInfo *> *)messageInfoList roomID:(NSString *)roomID;

/// 接收自定义信令通知
/// @param command 收到的信令内容
/// @param fromUser 信令的发送人
/// @param roomID 房间 ID
- (void)onIMRecvCustomCommand:(NSString *)command fromUser:(ZegoUser *)fromUser roomID:(NSString *)roomID;

@end


#pragma mark - Media Player

@protocol ZegoMediaPlayerEventHandler <NSObject>

@optional

/// 播放器播放状态回调
/// @param mediaPlayer 回调的播放器实例
/// @param state 播放器当前状态
/// @param errorCode 错误码
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer stateUpdate:(ZegoMediaPlayerState)state errorCode:(int)errorCode;

/// 播放器网络状态事件回调
/// @param mediaPlayer 回调的播放器实例
/// @param networkEvent 网络状态事件
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer networkEvent:(ZegoMediaPlayerNetworkEvent)networkEvent;

/// 播放器播放进度回调
/// @param mediaPlayer 回调的播放器实例
/// @param millisecond 进度，毫秒
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer playingProgress:(unsigned long long)millisecond;

@end


@protocol ZegoMediaPlayerVideoHandler <NSObject>

@optional

/// 播放器视频帧裸数据回调
/// @param mediaPlayer 回调的播放器实例
/// @param data 视频帧的裸数据（例：RGBA 只需考虑 data[0]，I420 需考虑 data[0,1,2]）
/// @param dataLength 数据的长度（例：RGBA 只需考虑 dataLength[0]，I420 需考虑 dataLength[0,1,2]）
/// @param param 视频帧参数
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFrameRawData:(const unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param;

/// 播放器视频帧 CVPixelBuffer 数据回调
/// @param mediaPlayer 回调的播放器实例
/// @param buffer 封装为 CVPixelBuffer 的视频帧数据
/// @param param 视频帧参数
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFramePixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param;

@end


@protocol ZegoMediaPlayerAudioHandler <NSObject>

@optional

/// 播放器音频帧数据回调
/// @param mediaPlayer 回调的播放器实例
/// @param data 音频帧的裸数据
/// @param dataLength 数据的长度
/// @param param 音频帧参数
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer audioFrameData:(const unsigned char *)data dataLength:(unsigned int)dataLength param:(ZegoAudioFrameParam *)param;

@end


#pragma mark - Custom Video IO

@protocol ZegoCustomVideoCaptureHandler <NSObject>

@optional

/// SDK 通知将要开始采集视频帧，收到该回调后向 SDK 发送的视频帧数据才有效
- (void)onStart;

/// SDK 通知将要停止采集视频帧
- (void)onStop;

@end


@protocol ZegoCustomVideoRenderHandler <NSObject>

@optional

/// 本地预览视频帧裸数据回调
/// @param data 视频帧的裸数据（例：RGBA 只需考虑 data[0]，I420 需考虑 data[0,1,2]）
/// @param dataLength 数据的长度（例：RGBA 只需考虑 dataLength[0]，I420 需考虑 dataLength[0,1,2]）
/// @param param 视频帧参数
/// @param flipMode 视频帧翻转模式
- (void)onCapturedVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode;

/// 远端拉流视频帧裸数据回调，通过 streamID 区分不同的流
/// @param data 视频帧的裸数据（例：RGBA 只需考虑 data[0]，I420 需考虑 data[0,1,2]）
/// @param dataLength 数据的长度（例：RGBA 只需考虑 dataLength[0]，I420 需考虑 dataLength[0,1,2]）
/// @param param 视频帧参数
/// @param streamID 远端拉流的流 ID
- (void)onRemoteVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param stream:(NSString *)streamID;

/// 本地预览视频帧 CVPixelBuffer 数据回调
/// @param buffer 封装为 CVPixelBuffer 的视频帧数据
/// @param param 视频帧参数
/// @param flipMode 视频帧翻转模式
- (void)onCapturedVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode;

/// 远端拉流视频帧 CVPixelBuffer 数据回调，通过 streamID 区分不同的流
/// @param buffer 封装为 CVPixelBuffer 的视频帧数据
/// @param param 视频帧参数
/// @param streamID 远端拉流的流 ID
- (void)onRemoteVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param stream:(NSString *)streamID;

@end

NS_ASSUME_NONNULL_END
