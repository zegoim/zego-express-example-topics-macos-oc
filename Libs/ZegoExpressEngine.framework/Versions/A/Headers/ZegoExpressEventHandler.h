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

/// Debug error message callback
///
/// When the APIs are not used correctly, the callback prompts for detailed error information, which is controlled by the [setDebugVerbose] interface
/// @param errorCode Error code, please refer to the common error code document [https://doc-zh.zego.im/zh/308.html] for details
/// @param funcName Function name
/// @param info Detailed error information
- (void)onDebugError:(int)errorCode funcName:(NSString *)funcName info:(NSString *)info;

#pragma mark Room Callback

/// Room status change callback
///
/// This callback is triggered when the connection status of the room changes, and the reason for the change is notified. Developers can use this callback to determine the status of the current user in the room. If the connection is being requested for a long time, the general probability is that the user's network is unstable.
/// @param state Changed room state
/// @param errorCode Error code, please refer to the [common error code document](https://doc-en.zego.im/en/308.html) for details
/// @param extendedData Extended Information
/// @param roomID Room ID, a string of up to 128 bytes in length.
- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode extendedData:(nullable NSDictionary *)extendedData roomID:(NSString *)roomID;

/// Notification callback for other users in the room to increase or decrease
///
/// Note that the callback is only triggered when the isUserStatusNotify parameter in the ZegoRoomConfig passed loginRoom function is YES. Developers can use this callback to determine the situation of users in the room.
/// When a user logs in to a room for the first time, other users already exist in this room, and a user list of the type of addition is received.
/// When the user is already in the room, other users in this room will trigger this callback to notify the changed users when they enter or exit the room.
/// @param updateType Update type (add/delete)
/// @param userList List of users changed in the current room
/// @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
- (void)onRoomUserUpdate:(ZegoUpdateType)updateType userList:(NSArray<ZegoUser *> *)userList roomID:(NSString *)roomID;

/// Notification of increase or decrease of streams published by other users in the same room
///
/// When a user logs in to a room for the first time, there are other users in the room who are publishing streams, and will receive a stream list of the added type.
/// When the user is already in the room, other users in this room will trigger this callback to notify the changed stream list when adding or deleting streams.
/// Developers can use this callback to determine if there are other users in the same room who have added or stopped streaming, in order to implement active play stream [startPlayingStream] or active stop playing stream [stopPlayingStream], and use simultaneous Changes to Streaming render UI widget;
/// @param updateType Update type (add/delete)
/// @param streamList Updated stream list
/// @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID;

/// Stream extra information update notification
///
/// When a user publishing the stream update the extra information of the stream in the same room, other users in the same room will receive the callback.
/// The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the publishing process, the stream extra information can be modified midway through the stream corresponding to the stream ID.
/// Developers can synchronize variable content related to stream IDs based on stream additional information.
/// @param streamList List of streams that the extra info was updated.
/// @param roomID Room ID where the user is logged in, a string of up to 128 bytes in length.
- (void)onRoomStreamExtraInfoUpdate:(NSArray<ZegoStream *> *)streamList roomID:(NSString *)roomID;

#pragma mark Publisher Callback

/// Publish stream state callback
///
/// After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
/// You can roughly judge the user's uplink network status based on whether the state parameter is in [PUBLISH_REQUESTING].
/// @param state Status of publishing stream
/// @param errorCode The error code corresponding to the status change of the publish stream. Please refer to the common error code documentation [https://doc-zh.zego.im/zh/308.html] for details.
/// @param extendedData Extended Information. If you use ZEGO's CDN content distribution network, after the stream is successfully published, the keys of the content of this parameter are flv_url_list, rtmp_url_list, hls_url_list. These correspond to the publishing stream URLs of the flv, rtmp, and hls protocols. For CDNs that do not use ZEGO, you do not need to pay attention to this parameter.
/// @param streamID Stream ID
- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode extendedData:(nullable NSDictionary *)extendedData streamID:(NSString *)streamID;

/// Publish stream quality callback
///
/// After the successful publish, the callback will be received every 3 seconds. Through the callback, the collection frame rate, bit rate, RTT, packet loss rate and other quality data of the published audio and video stream can be obtained, and the health of the publish stream can be monitored in real time.
/// You can monitor the health of the published audio and video streams in real time according to the quality parameters of the callback api, in order to show the uplink network status in real time on the device UI interface.
/// If you does not know how to use the parameters of this callback api, you can only pay attention to the level field of the quality parameter, which is a comprehensive value describing the uplink network calculated by SDK based on the quality parameters.
/// @param quality Published stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
/// @param streamID Stream ID
- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality streamID:(NSString *)streamID;

/// First frame callback notification for local audio captured
///
/// After the startPublishingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of audio data.
/// In the case of no startPublishingStream audio and video stream or preview, the first startPublishingStream audio and video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect audio data of the local device and receive this callback.
/// Developers can use this callback to determine whether SDK has actually collected audio data. If the callback is not received, the audio capture device is occupied or abnormal.
- (void)onPublisherCapturedAudioFirstFrame;

/// First frame callback notification for local video captured.
///
/// After the startPublishingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of video data.
/// In the case of no startPublishingStream video stream or preview, the first startPublishingStream video stream or first preview, that is, when the engine of the audio and video module inside SDK starts, it will collect video data of the local device and receive this callback.
/// Developers can use this callback to determine whether SDK has actually collected video data. If the callback is not received, the video capture device is occupied or abnormal.
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
- (void)onPublisherCapturedVideoFirstFrame:(ZegoPublishChannel)channel;

/// Video captured size change callback notification
///
/// After the successful publish, the callback will be received if there is a change in the video capture resolution in the process of publishing the stream.
/// When the audio and video stream is not published or previewed for the first time, the publishing stream or preview first time, that is, the engine of the audio and video module inside the SDK is started, the video data of the local device will be collected, and the collection resolution will change at this time.
/// You can use this callback to remove the cover of the local preview UI and similar operations.You can also dynamically adjust the scale of the preview view based on the resolution of the callback.
/// @param size Video capture resolution
/// @param channel Publishing stream channel.If you only publish one audio and video stream, you can ignore this parameter.
- (void)onPublisherVideoSizeChanged:(CGSize)size channel:(ZegoPublishChannel)channel;

/// Add/Remove CDN address status callback
///
/// After the ZEGO real-time audio and video cloud relays the audio and video streams to the CDN, this callback will be received if the CDN relay status changes, such as a stop or a retry.
/// Developers can use this callback to determine whether the audio and video streams of the relay CDN are normal. If they are abnormal, further locate the cause of the abnormal audio and video streams of the relay CDN and make corresponding disaster recovery strategies.
/// If you do not understand the cause of the abnormality, you can contact ZEGO technicians to analyze the specific cause of the abnormality.
/// @param infoList List of information that the current CDN is relaying
/// @param streamID Stream ID
- (void)onPublisherRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList streamID:(NSString *)streamID;

#pragma mark Player Callback

/// Play stream state callback
///
/// After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
/// You can roughly judge the user's downlink network status based on whether the state parameter is in [PLAY_REQUESTING].
/// @param state Current play state
/// @param errorCode The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-zh.zego.im/zh/308.html] for details.
/// @param extendedData Extended Information
/// @param streamID stream ID
- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode extendedData:(nullable NSDictionary *)extendedData streamID:(NSString *)streamID;

/// Play stream quality callback
///
/// After calling the startPlayingStream successfully, this callback will be triggered every 3 seconds. The collection frame rate, bit rate, RTT, packet loss rate and other quality data  can be obtained, such the health of the publish stream can be monitored in real time.
/// You can monitor the health of the played audio and video streams in real time according to the quality parameters of the callback api, in order to show the downlink network status on the device UI interface in real time.
/// If you does not know how to use the various parameters of the callback api, you can only focus on the level field of the quality parameter, which is a comprehensive value describing the downlink network calculated by SDK based on the quality parameters.
/// @param quality Playing stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
/// @param streamID Stream ID
- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality streamID:(NSString *)streamID;

/// Play media event callback
///
/// This callback is triggered when an event such as audio and video jamming and recovery occurs in the playing stream.
/// You can use this callback to make statistics on stutters or to make friendly displays in the UI interface of the app.
/// @param event Play media event callback
/// @param streamID Stream ID
- (void)onPlayerMediaEvent:(ZegoPlayerMediaEvent)event streamID:(NSString *)streamID;

/// First frame callback notification for remote audio received
///
/// After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of audio data.
/// @param streamID Stream ID
- (void)onPlayerRecvAudioFirstFrame:(NSString *)streamID;

/// First frame callback notification for remote video  received
///
/// After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it collects the first frame of video  data.
/// @param streamID Stream ID
- (void)onPlayerRecvVideoFirstFrame:(NSString *)streamID;

/// First video frame is rendered
///
/// After the startPlayingStream interface is called successfully, the SDK will receive this callback notification when it rendered the first frame of video  data.
/// You can use this callback to count time consuming that take the first frame time or update the playback stream.
/// @param streamID Stream ID
- (void)onPlayerRenderVideoFirstFrame:(NSString *)streamID;

/// playing stream resolution change callback
///
/// If there is a change in the video resolution of the playing stream, the callback will be triggered, and the user can adjust the display for that stream dynamically.
/// If the publishing stream end triggers the internal stream flow control of SDK due to a network problem, the encoding resolution of the streaming end may be dynamically reduced, and this callback will also be received at this time.
/// If the stream is only audio data, the callback will not be received.
/// This callback will be triggered when the played audio and video stream is actually rendered to the set UI play canvas. You can use this callback notification to update or switch UI components that actually play the stream.
/// @param size The resolution of the video
/// @param streamID Stream ID
- (void)onPlayerVideoSizeChanged:(CGSize)size streamID:(NSString *)streamID;

/// Receive SEI
///
/// If sendSEI was called on remote, this callback will be triggered.
/// If only the pure audio stream is played, the SEI information sent by the streaming end will not be received.
/// @param data SEI content
/// @param streamID Stream ID
- (void)onPlayerRecvSEI:(NSData *)data streamID:(NSString *)streamID;

#pragma mark Mixer Callback

/// Mixed stream relay CDN status update notification
///
/// In the general case of the ZEGO audio and video cloud mixing stream task, the output stream is published to the CDN using the rtmp protocol, and changes in the state during the publish will be notified from this callback api.
/// @param infoList List of information that the current CDN is being mixed
/// @param taskID Mix stream task ID
- (void)onMixerRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList taskID:(NSString *)taskID;

/// Callback when the soundLevel of every stream in the mix stream updated
///
/// You can use this callback to show the effect of the anchors sound level when the audience plays the mixed stream. So audience can notice which anchor is speaking.
/// @param soundLevels Sound level hash map, key is the soundLevelID of every single stream in this mixer stream, value is the sound level value of that single stream, value ranging from 0.0 to 100.0
- (void)onMixerSoundLevelUpdate:(NSDictionary<NSNumber *, NSNumber *> *)soundLevels;

#pragma mark Device Callback

#if TARGET_OS_OSX
/// Audio device status change
///
/// only for macOS; This callback is triggered when an audio device is added or removed from the system. By listening to this callback, users can update the sound collection or output using a specific device when necessary.
/// @param deviceInfo Audio device information
/// @param updateType Update type (add/delete)
/// @param deviceType Audio device type
- (void)onAudioDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType deviceType:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_OSX
/// Audio device status change
///
/// only for macOS; This callback is triggered when a video device is added or removed from the system. By listening to this callback, users can update the video capture using a specific device when necessary.
/// @param deviceInfo Audio device information
/// @param updateType Update type (add/delete)
- (void)onVideoDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType;
#endif

/// Captured sound level update callback
///
/// Callback notification period is 100 ms'
/// @param soundLevel Locally captured sound level value, ranging from 0.0 to 100.0
- (void)onCapturedSoundLevelUpdate:(NSNumber *)soundLevel;

/// Remote sound level update callback
///
/// Callback notification period is 100 ms'
/// @param soundLevels Remote sound level hash map, key is the streamID, value is the sound level value of the corresponding streamID, value ranging from 0.0 to 100.0
- (void)onRemoteSoundLevelUpdate:(NSDictionary<NSString *, NSNumber *> *)soundLevels;

/// Captured audio spectrum update callback
///
/// Callback notification period is 100 ms'
/// @param audioSpectrum Locally captured audio spectrum value list. Spectrum value range is [0-2^30]
- (void)onCapturedAudioSpectrumUpdate:(NSArray<NSNumber *> *)audioSpectrum;

/// Remote audio spectrum update callback
///
/// Callback notification period is 100 ms'
/// @param audioSpectrums Remote audio spectrum hash map, key is the streamID, value is the audio spectrum list of the corresponding streamID. Spectrum value range is [0-2^30]
- (void)onRemoteAudioSpectrumUpdate:(NSDictionary<NSString *, NSArray<NSNumber *> *> *)audioSpectrums;

/// Device exception notification
///
/// This callback is triggered when an exception occurs when reading or writing the audio and video device.
/// @param errorCode The error code corresponding to the status change of the playing stream. Please refer to the common error code documentation [https://doc-zh.zego.im/zh/308.html] for details
/// @param deviceName device name
- (void)onDeviceError:(int)errorCode deviceName:(NSString *)deviceName;

/// Remote camera device status notification
///
/// When the state of the remote camera device changes, such as switching the camera, by monitoring this callback, it is possible to obtain an event related to the far-end camera, which can be used to prompt the user that the video may be abnormal.
/// Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the camera device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
/// @param state Remote camera status
/// @param streamID Stream ID
- (void)onRemoteCameraStateUpdate:(ZegoRemoteDeviceState)state streamID:(NSString *)streamID;

/// Remote microphone device status notification
///
/// When the state of the remote microphone device is changed, such as switching a microphone, etc., by listening to the callback, it is possible to obtain an event related to the remote microphone, which can be used to prompt the user that the audio may be abnormal.
/// Developers of 1v1 education scenarios or education small class scenarios and similar scenarios can use this callback notification to determine whether the microphone device of the remote publishing stream device is working normally, and preliminary understand the cause of the device problem according to the corresponding state.
/// @param state Remote microphone status
/// @param streamID Stream ID
- (void)onRemoteMicStateUpdate:(ZegoRemoteDeviceState)state streamID:(NSString *)streamID;

#pragma mark IM Callback

/// Receive room broadcast message notification
///
/// @param messageList list of received messages.
/// @param roomID Room ID
- (void)onIMRecvBroadcastMessage:(NSArray<ZegoBroadcastMessageInfo *> *)messageList roomID:(NSString *)roomID;

/// Receive room barrage message notification
///
/// @param messageList list of received messages.
/// @param roomID Room ID
- (void)onIMRecvBarrageMessage:(NSArray<ZegoBarrageMessageInfo *> *)messageList roomID:(NSString *)roomID;

/// Receive room custom command notification
///
/// @param command Command content received
/// @param fromUser Sender of the command
/// @param roomID Room ID
- (void)onIMRecvCustomCommand:(NSString *)command fromUser:(ZegoUser *)fromUser roomID:(NSString *)roomID;

#pragma mark Deprecated Callback

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode room:(NSString *)room DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRoomUserUpdate:(ZegoUpdateType)updateType userList:(NSArray<ZegoUser *> *)userList room:(NSString *)room DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList room:(NSString *)room DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRoomStreamExtraInfoUpdate:(NSArray<ZegoStream *> *)streamList room:(NSString *)room DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use [onPublisherCapturedAudioFirstFrame], [onPublisherCapturedVideoFirstFrame:] instead
- (void)onPublisherRecvFirstFrameEvent:(ZegoPublisherFirstFrameEvent)event DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPublisherVideoSizeChanged:(CGSize)size DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPublisherRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)streamInfoList stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPlayerMediaEvent:(ZegoPlayerMediaEvent)event stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use [onPlayerRecvAudioFirstFrame:], [onPlayerRecvVideoFirstFrame:], [onPlayerRenderVideoFirstFrame:] instead
- (void)onPlayerRecvFirstFrameEvent:(ZegoPlayerFirstFrameEvent)event stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPlayerVideoSizeChanged:(CGSize)size stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onPlayerRecvSEI:(NSData *)data stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRemoteCameraStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRemoteMicStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

@end

#pragma mark - Zego Media Player Event Handler

@protocol ZegoMediaPlayerEventHandler <NSObject>

@optional

/// Media player playback status callback notification
///
/// @param mediaPlayer Callback player object
/// @param state Media player status
/// @param errorCode Error code, please refer to the common error code document [https://doc-zh.zego.im/zh/308.html] for details
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer stateUpdate:(ZegoMediaPlayerState)state errorCode:(int)errorCode;

/// Media player network status event callback notification
///
/// @param mediaPlayer Callback player object
/// @param networkEvent Network status event
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer networkEvent:(ZegoMediaPlayerNetworkEvent)networkEvent;

/// Media player playback progress notification
///
/// @param mediaPlayer Callback player object
/// @param millisecond Progress in milliseconds
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer playingProgress:(unsigned long long)millisecond;

@end

#pragma mark - Zego Media Player Video Handler

@protocol ZegoMediaPlayerVideoHandler <NSObject>

@optional

/// Callback notification of player throwing video data
///
/// @param mediaPlayer Callback player object
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame flip mode
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFrameRawData:(const unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param;

/// Callback notification of player throwing video data of CVPixelBuffer format
///
/// @param mediaPlayer Callback player object
/// @param buffer video data of CVPixelBuffer format
/// @param param video data frame param
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFramePixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param;

@end

#pragma mark - Zego Media Player Audio Handler

@protocol ZegoMediaPlayerAudioHandler <NSObject>

@optional

/// Callback notification of player throwing audio data
///
/// @param mediaPlayer Callback player object
/// @param data Raw data of audio frames
/// @param dataLength Data length
/// @param param audio frame flip mode
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer audioFrameData:(const unsigned char *)data dataLength:(unsigned int)dataLength param:(ZegoAudioFrameParam *)param;

@end

#pragma mark - Zego Custom Video Capture Handler

@protocol ZegoCustomVideoCaptureHandler <NSObject>

@optional

/// The SDK notifies that video frames are about to be collected, and the video frame data sent to the SDK is only valid after receiving the callback notification
///
/// @param channel Publishing stream channel.
- (void)onStart:(ZegoPublishChannel)channel;

/// SDK notifies to stop capturing video frames
///
/// @param channel Publishing stream channel.
- (void)onStop:(ZegoPublishChannel)channel;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onStart DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onStop DEPRECATED_ATTRIBUTE;

@end

#pragma mark - Zego Custom Video Render Handler

@protocol ZegoCustomVideoRenderHandler <NSObject>

@optional

/// Local preview video frame raw data callback
///
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame parameters
/// @param flipMode video flip mode
/// @param channel Publishing stream channel.
- (void)onCapturedVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode channel:(ZegoPublishChannel)channel;

/// Remote playing stream video frame raw data callback, you can differentiate different streams by streamID
///
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame parameters
/// @param streamID Stream ID
- (void)onRemoteVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param streamID:(NSString *)streamID;

/// Remote playing stream video frame raw data callback, you can differentiate different streams by streamID
///
/// @param buffer video data of CVPixelBuffer format
/// @param param Video frame param
/// @param flipMode video flip mode
/// @param channel Publishing stream channel.
- (void)onCapturedVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode channel:(ZegoPublishChannel)channel;

/// Remote playing stream video frame CVPixelBuffer data callback, you can differentiate different streams by streamID
///
/// @param buffer video data of CVPixelBuffer format
/// @param param Video frame param
/// @param streamID Stream ID
- (void)onRemoteVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param streamID:(NSString *)streamID;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onCapturedVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRemoteVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onCapturedVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode DEPRECATED_ATTRIBUTE;

/// @deprecated This callback is deprecated, please use the overloaded interface with the same name
- (void)onRemoteVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param stream:(NSString *)stream DEPRECATED_ATTRIBUTE;

@end

NS_ASSUME_NONNULL_END
