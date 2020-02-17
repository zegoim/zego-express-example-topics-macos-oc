//
//  ZegoExpressEngine+Player.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Player)

/// 开始拉流
/// @discussion 可通过此接口让用户可以从 ZEGO 实时音视频云拉取远端用户的音视频流进行互通。在开始拉流前，需要先加入房间，可通过监听 onRoomStreamUpdate:streamList:room: 事件回调来获取该房间内 streamID 的新增。在网络质量不佳的情况下，用户拉流可能出现中断， SDK 会尝试重新连接，可通过监听 onPlayerStateUpdate:errorCode:stream: 事件来获知当前拉流状态以及错误信息。拉取不存在的流 ID，执行本接口后 SDK 持续尝试拉取，在该流 ID 被成功推送后，音视频流可以真正被拉取到。开发者可通过再次调用此接口实现更换拉流 Canvas 的操作（流 ID 必须一样）。
/// @param streamID 流 ID
/// @param canvas 用于显示拉流画面的视图，视图设置为空则不进行显示。
- (void)startPlayingStream:(NSString *)streamID canvas:(nullable ZegoCanvas *)canvas;

/// 停止拉流
/// @discussion 可通过此接口让用户停止拉取远端的音视频流。停止拉流后对此条流此前设置的属性如 setPlayVolume:stream:、mutePlayStreamAudio:stream:、mutePlayStreamVideo:stream: 等都会失效，需要在下次拉流时重新设置。
/// @param streamID 流 ID
- (void)stopPlayingStream:(NSString *)streamID;

/// 设置拉流音量
/// @discussion 此接口用于设置拉流的声音大小，本端用户可控制音频流的播放音量。需要在调用拉流接口后调用。
/// @param volume 音量百分比
/// @param streamID 流 ID
- (void)setPlayVolume:(int)volume stream:(NSString *)streamID;

/// 停止或恢复拉取音频流
/// @discussion 拉流时可调用此接口实现不拉取远端用户的音频数据，需要在调用拉流接口后调用。
/// @param mute 禁用标识。YES:禁止拉取；NO:恢复拉取。
/// @param streamID 流 ID
- (void)mutePlayStreamAudio:(BOOL)mute stream:(NSString *)streamID;

/// 停止或恢复拉取视频流
/// @discussion 拉流时可调用此接口实现不拉取远端用户的视频数据，需要在调用拉流接口后调用。
/// @param mute 禁用标识。YES:禁止拉取；NO:恢复拉取。
/// @param streamID 流 ID
- (void)mutePlayStreamVideo:(BOOL)mute stream:(NSString *)streamID;

/// 开/关硬件解码
/// @discussion 拉流时是否使用硬件解码，开启硬件解码后SDK会使用GPU进行解码，降低CPU使用率。在拉流前设置才能生效，如果在拉流后设置，停止拉流后重新拉流可以生效。
/// @param enable 是否开启硬解开关。YES:启用硬解；NO:关闭硬解。
- (void)enableHardwareDecoder:(BOOL)enable;

/// 开/关帧顺序检测
/// @param enable YES  检测帧顺序，不支持B帧； NO 不检测帧顺序，支持B帧，可能出现短暂花屏
- (void)enableCheckPoc:(BOOL)enable;

@end

NS_ASSUME_NONNULL_END
