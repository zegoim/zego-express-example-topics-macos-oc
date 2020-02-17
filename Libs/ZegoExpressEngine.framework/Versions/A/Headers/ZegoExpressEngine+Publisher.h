//
//  ZegoExpressEngine+Publisher.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Publisher)

/// 开始推流
/// @discussion 可通过此接口让用户将自己本地的音视频流推送到 ZEGO 实时音视频云，同一房间的其他用户通过 streamID 就可以拉取该音视频流进行互通。在开始推流前，需要先加入房间，同房间内其他用户可通过监听 onRoomStreamUpdate:streamList:room: 事件回调来获取该 streamID 新增。在网络质量不佳的情况下，用户推流可能出现中断， SDK 会尝试重新连接，可通过监听 onPublisherStateUpdate:errorCode:stream: 事件来获知当前推流状态以及错误信息。
/// @param streamID 流 ID，长度不超过256的字符串，需要在整个 AppID 内全局唯一，若出现在同一个 AppID 内，不同的用户各推了一条流且流名相同 ，将会导致后推流的用户推流失败
- (void)startPublishing:(NSString *)streamID;

/// 停止推流
/// @discussion 可通过此接口让用户停止发送本地的音视频流，结束通话。如果用户已经启动推流，在推新流（新的streamID）之前，必须要调用此接口停止当前流的推送，否则新流推送会返回失败。
- (void)stopPublishing;

/// 设置流附加信息
/// @discussion 可通过此接口设置当前推流的流附加信息，设置结果会通过 ZegoPublisherSetStreamExtraInfoCallback 回调通知。
/// @param extraInfo 流附加信息，长度不超过1024的字符串。
/// @param callback 更新流附加信息执行结果通知
- (void)setStreamExtraInfo:(NSString *)extraInfo callback:(nullable ZegoPublisherSetStreamExtraInfoCallback)callback;

/// 启动/更新本地预览
/// @discussion 用户通过调用此接口可以看到自己本地的画面。预览功能不需要先登陆房间或推流。可以通过再次调用该接口来更新本地视图和视图预览模式。可以通过调用 setVideoMirrorMode: 接口来设置预览的镜像模式，默认为开启预览镜像。
/// @param canvas 启动预览时用于显示画面的视图，视图设置为空则不进行预览。
- (void)startPreview:(nullable ZegoCanvas *)canvas;

/// 停止本地预览
/// @discussion 当本地不需要看到预览画面时可调用此接口停止预览。
- (void)stopPreview;

/// 设置视频配置
/// @discussion 可通过此接口设置视频帧率、码率，视频采集分辨率，视频编码输出分辨率。如果不调用此接口，默认分辨率为 360p，码率为 600 kbps，帧率为 15 fps。需要在推流前设置好相关视频配置，在推流后仅支持编码分辨率和码率的修改。
/// @param videoConfig 视频配置，SDK 提供常用的分辨率、帧率和码率的组合值，也可自定义分辨率、帧率和码率
- (void)setVideoConfig:(ZegoVideoConfig *)videoConfig;

/// 设置镜像模式
/// @discussion 可调用此接口来设置本地预览视频以及推送的视频是否开启镜像模式。
/// @param mirrorMode 预览或推流的镜像模式。
- (void)setVideoMirrorMode:(ZegoVideoMirrorMode)mirrorMode;

#if TARGET_OS_IPHONE
/// 设置采集视频的朝向
/// @discussion 此接口可设置视频的朝向方位，相比与手机正立的正向，将采集到的数据按照参数 UIInterfaceOrientation 的枚举值进行旋转，旋转后会自动进行调整，以适配编码后的图像分辨率。
/// @param orientation 视频的朝向。
- (void)setAppOrientation:(UIInterfaceOrientation)orientation;
#endif

/// 设置音频质量配置
/// @discussion 可通过此接口设置音频编码类型、码率，声道数的组合值。如果不调用此接口，默认为“普通延迟-标准音质”模式。仅支持推流前设置。
/// @param config 音频质量配置
- (void)setAudioConfig:(ZegoAudioConfig *)config;

/// 停止或恢复发送音频流
/// @discussion 推流时可调用此接口实现只推视频流不推音频，本地仍会采集和处理音频，但不向网络发送音频数据。可以在推流前设置。如果在本地设置了停止发送音频流，对端可以通过监听 onRemoteMicStateUpdate:stream: 回调收到 ZegoRemoteDeviceStateMute 的状态变更通知。
/// @param mute 是否停止发送音频流，YES 表示只发送视频流不发送音频流，NO 表示同时发送音频和视频流。默认为 NO。
- (void)mutePublishStreamAudio:(BOOL)mute;

/// 停止或恢复发送视频流
/// @discussion 推流时可调用此接口实现只推音频流不推视频流，本地摄像头仍能正常工作，能正常采集，预览和处理视频画面，但不向网络发送视频数据。可以在推流前设置。如果在本地设置了停止发送视频流，对端可以通过监听 onRemoteCameraStateUpdate:stream: 回调收到 ZegoRemoteDeviceStateMute 的状态变更通知。
/// @param mute 是否停止发送视频流，YES 表示只发送音频流不发送视频流，NO 表示同时发送音频和视频流。默认为 NO。
- (void)mutePublishStreamVideo:(BOOL)mute;

/// 设置推流端采集音量
/// @discussion 此接口用于设置音频的采集音量，本端用户可控制往远端发送音频流的声音大小。可以在推流前设置。
/// @param volume 音量百分比，默认值为100
- (void)setCaptureVolume:(int)volume;

/// 增加转推至 CDN 的 URL
/// @discussion 当需要将音视频流转推到其它指定的 CDN 时需要调用此接口进行设置。
/// @param targetURL CDN 转推地址，支持的转推地址格式有 rtmp，flv，hls
/// @param streamID 需要转推的流 ID
/// @param callback 添加 CDN 转推结果通知
- (void)addPublishCDNURL:(NSString *)targetURL stream:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// 删除转推至 CDN 的 URL
/// @discussion 当已经添加了某个 CDN 转推地址，需要停止将流停止转推至该接口时调用此接口。
/// @param targetURL CDN 转推地址，支持的转推地址格式有 rtmp，flv，hls
/// @param streamID 需要停止转推的流 ID
/// @param callback 移除 CDN 转推结果通知
- (void)removePublishCDNURL:(NSString *)targetURL stream:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// 设置推流水印
/// @discussion 推流前设置，水印的布局不能超出推流的视频编码分辨率。
/// @param watermark 水印布局左上角为坐标系原点，区域不能超过编码分辨率设置的大小
/// @param isPreviewVisible 是否本地预览能看见水印
- (void)setPublishWatermark:(ZegoWatermark *)watermark isPreviewVisible:(BOOL)isPreviewVisible;

/// 发送媒体增强补充信息
/// @discussion 此接口可在开发者推流传输音视频流数据同时，发送流媒体增强补充信息来同步一些其他附加信息。一般如同步音乐歌词或视频画面精准布局等场景，可选择使用发送 SEI。当推流方发送 SEI 后，拉流方可通过监听 onPlayerRecvSEI 的回调获取SEI内容。
/// @param data SEI 内容
- (void)sendSEI:(NSData *)data;

/// 开/关硬件编码
/// @discussion 推流时是否采用硬件编码的开关，开启硬解编码后会使用 GPU 进行编码，降低 CPU 使用率。在推流前设置才能生效，如果在推流后设置，停推后重新推流可以生效。
/// @param enable 是否开启硬件编码。YES 表示开启硬件编码，NO 表示关闭硬件编码。
- (void)enableHardwareEncoder:(BOOL)enable;

/// 设置采集时机
/// @param mode 采集时机
- (void)setCapturePipelineScaleMode:(ZegoCapturePipelineScaleMode)mode;

@end

NS_ASSUME_NONNULL_END
