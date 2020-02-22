//
//  ZegoExpressEngine+Publisher.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Publisher)

/// Start publishing stream
/// @discussion This interface allows users to publish their local audio and video streams to the ZEGO real-time audio and video cloud. Other users in the same room can use the streamID to pull the audio and video streams for intercommunication.Before you start to push the stream, you need to join the room first. Other users in the same room can get the streamID by monitoring the onRoomStreamUpdate:streamList:room: event callback.In the case of poor network quality, user push may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error infomation of the stream published by monitoring the onPublisherStateUpdate:errorCode:stream: event.
/// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users push each stream and the stream ID is the same, which will cause the user to push the stream failure.
- (void)startPublishing:(NSString *)streamID;

/// Stop publishing stream
/// @discussion This interface allows the user to stop sending local audio and video streams and end the call. If the user has initiated publish flow, this interface must be called to stop the publish of the current stream before pushing the new stream (new streamID), otherwise the new stream push will return a failure.
- (void)stopPublishing;

/// Set stream extra information
/// @discussion User this interface to set the extra info of the stream, the result will be notified via the ZegoPublisherSetStreamExtraInfoCallback.
/// @param extraInfo Stream extra information, a string of up to 1024 characters.
/// @param callback Set stream extra information execution result notification
- (void)setStreamExtraInfo:(NSString *)extraInfo callback:(nullable ZegoPublisherSetStreamExtraInfoCallback)callback;

/// Start/Update local preview
/// @discussion The user can see his own local image by calling this interface. The preview function does not require you to log in to the room or push the stream first.Local view and preview modes can be updated by calling this interface again.You can set the mirror mode of the preview by calling the setVideoMirrorMode: interface. The default preview setting is image mirrored. 
/// @param canvas The view used to display the preview image. If the view is set to empty, no preview will be made.
- (void)startPreview:(nullable ZegoCanvas *)canvas;

/// Stop local preview
/// @discussion This interface can be called to stop previewing when there is no need to see the preview image locally.
- (void)stopPreview;

/// Set up video configuration
/// @discussion This interface can be used to set the video frame rate, bit rate, video capture resolution, and video encoding output resolution. If you do not call this interface, the default resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps. It is necessary to set the relevant video configuration before pushing the stream, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
/// @param videoConfig Video configuration, the SDK provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
- (void)setVideoConfig:(ZegoVideoConfig *)videoConfig;

/// Set mirror mode
/// @discussion This interface can be called to set whether the local preview video and the published video have mirror mode enabled.
/// @param mirrorMode Mirror mode for previewing or publishing the stream
- (void)setVideoMirrorMode:(ZegoVideoMirrorMode)mirrorMode;

#if TARGET_OS_IPHONE
/// Set the orientation of the captured video
/// @discussion This interface can set the orientation of the video. Compared with the forward direction of the mobile phone, the collected data is rotated according to the value of the parameter UIInterfaceOrientation. After the rotation, it will be automatically adjusted to adapt the encoded image resolution. .
/// @param orientation Video orientation
- (void)setAppOrientation:(UIInterfaceOrientation)orientation;
#endif

/// set audio config
/// @discussion You can set the combined value of the audio codec, bit rate, and number of channels through this interface. If this interface is not called, the default is "normal_latency_standard_quality" mode. Should be used before publishing.
/// @param config Audio config
- (void)setAudioConfig:(ZegoAudioConfig *)config;

/// Stop or resume sending audio streams
/// @discussion This interface can be called when publishing the stream to push only the video stream without pushing the audio. The SDK still collects and processes the audio, but does not send the audio data to the network. It can be set before publishing.If you stop sending audio streams, the peer can receive  ZegoRemoteDeviceStateMute status change notification by monitoring onRemoteMicStateUpdate:stream: callbacks,
/// @param mute Whether to stop sending audio streams, YES means that only the video stream is sent without sending the audio stream, and NO means that the audio and video streams are sent simultaneously. The default is NO.
- (void)mutePublishStreamAudio:(BOOL)mute;

/// Stop or resume sending a video stream
/// @discussion When publishing the stream, this interface can be called to push only the audio stream without pushing the video stream. The local camera can still work normally, and can normally capture, preview and process the video picture, but does not send the video data to the network. It can be set before publishing.If you stop sending video streams locally, the peer can receive ZegoRemoteDeviceStateMute status change notification by monitoring onRemoteCameraStateUpdate:stream: callbacks,
/// @param mute Whether to stop sending video streams, YES means that only the audio stream is sent without sending the video stream, and NO means that the audio and video streams are sent at the same time. The default is NO.
- (void)mutePublishStreamVideo:(BOOL)mute;

/// Set the captured volume for publishing stream
/// @discussion This interface is used to set the audio collection volume. The local user can control the volume of the audio stream sent to the far end. It can be set before publishing.
/// @param volume Volume percentage, default is 100
- (void)setCaptureVolume:(int)volume;

/// Add URL to relay to CDN
/// @discussion This interface needs to be called for setting when you need to transfer audio and video streams to other specified CDNs.
/// @param targetURL Stream ID that needs to be relayed
/// @param streamID CDN relay address, supported address format rtmp, flv, hls
/// @param callback The execution result notification of the relay CDN operation, and proceed to the next step according to the execution result.
- (void)addPublishCDNURL:(NSString *)targetURL stream:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// Delete the URL relayed to the CDN
/// @discussion This interface is called when a CDN relayed address has been added and needs to stop propagating the stream to the CDN.
/// @param targetURL Stream ID that needs to stop relay
/// @param streamID CDN relay address, supported address format rtmp, flv, hls
/// @param callback Remove CDN relay result notifications
- (void)removePublishCDNURL:(NSString *)targetURL stream:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// set publish watermark
/// @discussion Set before publishing. The layout of the watermark cannot exceed the video encoding resolution of stream.
/// @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution.
/// @param isPreviewVisible the watermark is visible on local preview
- (void)setPublishWatermark:(ZegoWatermark *)watermark isPreviewVisible:(BOOL)isPreviewVisible;

/// Send SEI
/// @param data SEI data
- (void)sendSEI:(NSData *)data;

/// On/off hardware encoding
/// @discussion Whether to use the hardware encoding function when publishing the stream, the GPU is used to encode the stream and to reduce the CPU usage. The setting can take effect before the stream published. If it is set after the stream published, the stream should be stopped first before it takes effect.
/// @param enable Whether to enable hardware encoding. True means that the hardware encoding is turned on, and false means that the hardware encoding is turned off.
- (void)enableHardwareEncoder:(BOOL)enable;

/// set capture pipline scale mode
/// @param mode capture mode
- (void)setCapturePipelineScaleMode:(ZegoCapturePipelineScaleMode)mode;

@end

NS_ASSUME_NONNULL_END
