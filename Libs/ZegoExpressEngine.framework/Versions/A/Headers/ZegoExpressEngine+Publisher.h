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
///
/// This interface allows users to publish their local audio and video streams to the ZEGO real-time audio and video cloud. Other users in the same room can use the streamID to pull the audio and video streams for intercommunication.
/// Before you start to push the stream, you need to join the room first by calling [loginRoom]. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the loacal user publishing stream successfully.
/// In the case of poor network quality, user push may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error infomation of the stream published by monitoring the [onPublisherStateUpdate] event.
/// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users push each stream and the stream ID is the same, which will cause the user to push the stream failure.
- (void)startPublishing:(NSString *)streamID;

/// Start publishing stream, you can call this api to piblish the another stream.
///
/// This interface allows users to publish their local audio and video streams to the ZEGO real-time audio and video cloud. Other users in the same room can use the streamID to pull the audio and video streams for intercommunication.
/// Before you start to push the stream, you need to join the room first by calling [loginRoom]. Other users in the same room can get the streamID by monitoring the [onRoomStreamUpdate] event callback after the loacal user publishing stream successfully.
/// In the case of poor network quality, user push may be interrupted, and the SDK will attempt to reconnect. You can learn about the current state and error infomation of the stream published by monitoring the [onPublisherStateUpdate] event.
/// @param streamID Stream ID, a string of up to 256 characters, needs to be globally unique within the entire AppID. If in the same AppID, different users push each stream and the stream ID is the same, which will cause the user to push the stream failure.
/// @param channel Publish stream channel
- (void)startPublishing:(NSString *)streamID channel:(ZegoPublishChannel)channel;

/// Stop publishing stream
///
/// This interface allows the user to stop sending local audio and video streams and end the call.
/// If the user has initiated publish flow, this interface must be called to stop the publish of the current stream before pushing the new stream (new streamID), otherwise the new stream push will return a failure.
/// After stopping streaming, the developer should stop the local preview based on whether the business situation requires it.
- (void)stopPublishing;

/// Stop publishing stream of the specified channel
///
/// This interface allows the user to stop sending local audio and video streams and end the call.
/// If the user has initiated publish flow, this interface must be called to stop the publish of the current stream before pushing the new stream (new streamID), otherwise the new stream push will return a failure.
/// After stopping streaming, the developer should stop the local preview based on whether the business situation requires it.
/// Use this API to stop publishing stream of aux channel.
/// @param channel Publish stream channel
- (void)stopPublishing:(ZegoPublishChannel)channel;

/// Set stream extra information
///
/// User this interface to set the extra info of the stream, the result will be notified via the [ZegoPublisherSetStreamExtraInfoCallback].
/// The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the pushing process, the stream extra information can be modified midway through the stream corresponding to the stream ID.
/// Developers can synchronize variable content related to stream IDs based on stream additional information.
/// @param extraInfo Stream extra information, a string of up to 1024 characters.
/// @param callback Set stream extra information execution result notification
- (void)setStreamExtraInfo:(NSString *)extraInfo callback:(nullable ZegoPublisherSetStreamExtraInfoCallback)callback;

/// Set stream additional information. You can call this api to set params when pushing another streams
///
/// User this interface to set the extra info of the stream, the result will be notified via the [ZegoPublisherSetStreamExtraInfoCallback].
/// The stream extra information is an extra information identifier of the stream ID. Unlike the stream ID, which cannot be modified during the pushing process, the stream extra information can be modified midway through the stream corresponding to the stream ID.
/// Developers can synchronize variable content related to stream IDs based on stream additional information.
/// @param extraInfo Stream extra information, a string of up to 1024 characters.
/// @param callback Set stream extra information execution result notification
/// @param channel Publish stream channel
- (void)setStreamExtraInfo:(NSString *)extraInfo callback:(nullable ZegoPublisherSetStreamExtraInfoCallback)callback channel:(ZegoPublishChannel)channel;

/// Start/Update local preview
///
/// The user can see his own local image by calling this interface. The preview function does not require you to log in to the room or push the stream first. But after exiting the room, ZegoExpressEngine internally actively stops previewing by default.
/// Local view and preview modes can be updated by calling this interface again.
/// You can set the mirror mode of the preview by calling the [setVideoMirrorMode] interface. The default preview setting is image mirrored.
/// When this api is called, the audio and video engine module inside ZegoExpressEngine will start really, and it will start to try to collect audio and video. In addition to calling this api normally to preview the local screen, developers can also pass [nil] to the canvas parameter, in conjunction with ZegoExpressEngine's sound wave function, in order to achieve the purpose of detecting whether the audio equipment is working properly before logging in to the room.
/// @param canvas The view used to display the preview image. If the view is set to nil, no preview will be made.
- (void)startPreview:(nullable ZegoCanvas *)canvas;

/// Start/Update local preview. You can call this api to set params when pushing another streams
///
/// The user can see his own local image by calling this interface. The preview function does not require you to log in to the room or push the stream first. But after exiting the room, ZegoExpressEngine internally actively stops previewing by default.
/// Local view and preview modes can be updated by calling this interface again.
/// You can set the mirror mode of the preview by calling the [setVideoMirrorMode] interface. The default preview setting is image mirrored.
/// When this api is called, the audio and video engine module inside ZegoExpressEngine will start really, and it will start to try to collect audio and video. In addition to calling this api normally to preview the local screen, developers can also pass [nil] to the canvas parameter, in conjunction with ZegoExpressEngine's sound wave function, in order to achieve the purpose of detecting whether the audio equipment is working properly before logging in to the room.
/// @param canvas The view used to display the preview image. If the view is set to nil, no preview will be made.
/// @param channel Publish stream channel
- (void)startPreview:(nullable ZegoCanvas *)canvas channel:(ZegoPublishChannel)channel;

/// Stop local preview
///
/// This api can be called to stop previewing when there is no need to see the preview locally.
- (void)stopPreview;

/// Stop local preview
///
/// This api can be called to stop previewing when there is no need to see the preview locally.
/// @param channel Publish stream channel
- (void)stopPreview:(ZegoPublishChannel)channel;

/// Set up video configuration
///
/// This api can be used to set the video frame rate, bit rate, video capture resolution, and video encoding output resolution. If you do not call this api, the default resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps.
/// It is necessary to set the relevant video configuration before pushing the stream, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
/// Developers should note that the wide and high resolution of the mobile end is opposite to the wide and high resolution of the PC. For example, in the case of 360p, the resolution of the mobile end is 360x640, and the resolution of the PC end is 640x360.
/// @param videoConfig Video configuration, the ZegoExpressEngine provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
- (void)setVideoConfig:(ZegoVideoConfig *)videoConfig;

/// Set up video configuration. You can call this api to publish another streams
///
/// This api can be used to set the video frame rate, bit rate, video capture resolution, and video encoding output resolution. If you do not call this api, the default resolution is 360p, the bit rate is 600 kbps, and the frame rate is 15 fps.
/// It is necessary to set the relevant video configuration before pushing the stream, and only support the modification of the encoding resolution and the bit rate after publishing the stream.
/// Developers should note that the wide and high resolution of the mobile end is opposite to the wide and high resolution of the PC. For example, in the case of 360p, the resolution of the mobile end is 360x640, and the resolution of the PC end is 640x360.
/// @param videoConfig Video configuration, the ZegoExpressEngine provides a common setting combination of resolution, frame rate and bit rate, they also can be customized.
/// @param channel Publish stream channel
- (void)setVideoConfig:(ZegoVideoConfig *)videoConfig channel:(ZegoPublishChannel)channel;

/// Set mirror mode
///
/// This interface can be called to set whether the local preview video and the published video have mirror mode enabled.
/// @param mirrorMode Mirror mode for previewing or publishing the stream
- (void)setVideoMirrorMode:(ZegoVideoMirrorMode)mirrorMode;

/// Set mirror mode. You can call this api to set params when pushing another streams
///
/// This interface can be called to set whether the local preview video and the published video have mirror mode enabled.
/// @param mirrorMode Mirror mode for previewing or publishing the stream
/// @param channel Publish stream channel
- (void)setVideoMirrorMode:(ZegoVideoMirrorMode)mirrorMode channel:(ZegoPublishChannel)channel;

#if TARGET_OS_IPHONE
/// Set the orientation of video
///
/// This interface can set the orientation of the video. Compared with the forward direction of the mobile phone, the collected data is rotated according to the value of the parameter UIInterfaceOrientation. After the rotation, it will be automatically adjusted to adapt the encoded image resolution.
/// @param orientation Video orientation
- (void)setAppOrientation:(UIInterfaceOrientation)orientation;
#endif

#if TARGET_OS_IPHONE
/// Set the orientation of the captured video. You can call this api to set params when pushing another streams.
///
/// This interface can set the orientation of the video. Compared with the forward direction of the mobile phone, the collected data is rotated according to the value of the parameter UIInterfaceOrientation. After the rotation, it will be automatically adjusted to adapt the encoded image resolution.
/// @param orientation Video orientation
/// @param channel Publish stream channel
- (void)setAppOrientation:(UIInterfaceOrientation)orientation channel:(ZegoPublishChannel)channel;
#endif

/// set audio config
///
/// You can set the combined value of the audio codec, bit rate, and audio channel through this interface. If this interface is not called, the default is "nornal_latency_standard_quality" mode. Should be used before publishing.
/// If the preset value cannot meet the developer's scenario, the developer can set the parameters according to the business requirements.
/// @param config Audio config
- (void)setAudioConfig:(ZegoAudioConfig *)config;

/// Stop or resume sending a audio stream
///
/// This interface can be called when publishing the stream to push only the video stream without pushing the audio. The SDK still collects and processes the audio, but does not send the audio data to the network. It can be set before publishing.
/// If you stop sending audio streams, the remote user that play stream of local user pusihng stream can receive ZEGO_REMOTE_DEVICE_STATE_MUTE status change notification by monitoring [onRemoteMicStateUpdate] callbacks,
/// @param mute Whether to stop sending audio streams, YES means that only the video stream is sent without sending the audio stream, and NO means that the audio and video streams are sent simultaneously. The default is NO.
- (void)mutePublishStreamAudio:(BOOL)mute;

/// Stop or resume sending a audio stream. You can call this api to set params when pushing another streams
///
/// This interface can be called when publishing the stream to push only the video stream without pushing the audio. The SDK still collects and processes the audio, but does not send the audio data to the network. It can be set before publishing.
/// If you stop sending audio streams, the remote user that play stream of local user pusihng stream can receive  ZEGO_REMOTE_DEVICE_STATE_MUTE status change notification by monitoring [onRemoteMicStateUpdate] callbacks,
/// @param mute Whether to stop sending audio streams, YES means that only the video stream is sent without sending the audio stream, and NO means that the audio and video streams are sent simultaneously. The default is NO.
/// @param channel Publish stream channel
- (void)mutePublishStreamAudio:(BOOL)mute channel:(ZegoPublishChannel)channel;

/// Stop or resume sending a video stream
///
/// When publishing the stream, this interface can be called to push only the audio stream without pushing the video stream. The local camera can still work normally, and can normally capture, preview and process the video picture, but does not send the video data to the network. It can be set before publishing.
/// If you stop sending video streams locally, the remote user that play stream of local user pusihng stream can receive ZEGO_REMOTE_DEVICE_STATE_MUTE status change notification by monitoring [onRemoteCameraStateUpdate] callbacks,
/// @param mute Whether to stop sending video streams, YES means that only the audio stream is sent without sending the video stream, and NO means that the audio and video streams are sent at the same time. The default is NO.
- (void)mutePublishStreamVideo:(BOOL)mute;

/// Stop or resume sending a video stream. You can call this api to set params when pushing another streams
///
/// When publishing the stream, this interface can be called to push only the audio stream without pushing the video stream. The local camera can still work normally, and can normally capture, preview and process the video picture, but does not send the video data to the network. It can be set before publishing.
/// If you stop sending video streams locally, the remote user that play stream of local user pusihng stream can receive ZEGO_REMOTE_DEVICE_STATE_MUTE status change notification by monitoring [onRemoteCameraStateUpdate] callbacks,
/// @param mute Whether to stop sending video streams, YES means that only the audio stream is sent without sending the video stream, and NO means that the audio and video streams are sent at the same time. The default is NO.
/// @param channel Publish stream channel
- (void)mutePublishStreamVideo:(BOOL)mute channel:(ZegoPublishChannel)channel;

/// Enable or disable traffic control
///
/// Traffic control enables ZegoExpressEngine SDK to dynamically adjust the bitrate of audio and video streaming according to its own and peer current network environment status.
/// Automatically adapt to the current network environment and fluctuations, so as to ensure the smooth publishing of stream.
/// @param enable Whether to enable traffic control. The default is ture.
/// @param property Adjustable property of traffic control. Should be one or the combinations of ZegoTrafficControlProperty enumeration. AdaptiveFPS as default.
- (void)enableTrafficControl:(BOOL)enable property:(ZegoTrafficControlProperty)property;

/// Set the minimum video birtate for traffic control
///
/// Set how should SDK send video data when the network conditions are poor and the minimum video birrate cannot be met.
/// When this api is not called, the ZegoExpressEngine SDK will automatically adjust the sent video data frames according to the current network uplink conditions by default.
/// @param bitrate Minimum video bitrate (kbps)
/// @param mode Video sending mode below the minimum bitrate.
- (void)setMinVideoBitrateForTrafficControl:(int)bitrate mode:(ZegoTrafficControlMinVideoBitrateMode)mode;

/// Set the captured volume for publishing stream
///
/// This interface is used to set the audio collection volume. The local user can control the volume of the audio stream sent to the far end. It can be set before publishing.
/// @param volume Volume percentage. The range is 0 to 100. Default value is 100.
- (void)setCaptureVolume:(int)volume;

/// Add URL to relay to CDN
///
/// You can call this api to push the audio and video streams that have been pushed to the ZEGO real-time audio and video cloud to a custom CDN content distribution network that has high latency but supports high concurrent playing stream.
/// Because this called api is essentially a dynamic retweet of the audio and video streams pushed to the ZEGO audio and video cloud to different CDNs, this api needs to be called after the audio and video stream is published to ZEGO real-time cloud successfully.
/// Since ZEGO's audio and video cloud service itself can be configured to support CDN(content distribution networks), this api is mainly used by developers who have CDN content distribution services themselves.
/// You can use ZEGO's CDN audio and video streaming content distribution service at the same time by calling this interface and then use the developer who owns the CDN content distribution service.
/// This interface supports dynamic retweets to the CDN content distribution network, so developers can use this api as a disaster recovery solution for CDN content distribution services.
/// When the [enablePublishDirectToCDN] api is set to YES to push the stream straight to the CDN, then calling this interface will have no effect.
/// @param targetURL CDN relay address, supported address format rtmp.
/// @param streamID Stream ID that needs to be relayed, a string of up to 256 characters.
/// @param callback The execution result notification of the relay CDN operation, and proceed to the next step according to the execution result.
- (void)addPublishCDNURL:(NSString *)targetURL streamID:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// Delete the URL relayed to the CDN
///
/// This api is called when a CDN relayed address has been added and needs to stop propagating the stream to the CDN.
/// This api does not stop publishing audio and video stream to the ZEGO audio and video cloud.
/// @param targetURL CDN relay address, supported address format rtmp, flv, hls
/// @param streamID Stream ID that needs to stop relay, a string of up to 256 characters.
/// @param callback Remove CDN relay result notifications
- (void)removePublishCDNURL:(NSString *)targetURL streamID:(NSString *)streamID callback:(nullable ZegoPublisherUpdateCDNURLCallback)callback;

/// Whether to publish stream directly to CDN without passing through Zego real-time video cloud server
///
/// @param enable Whether to enable direct push CDN, YES: enable direct push CDN, NO: disable direct push CDN
/// @param config CDN configuration, if nil, use Zego's background default configuration
- (void)enablePublishDirectToCDN:(BOOL)enable config:(nullable ZegoCDNConfig *)config;

/// Whether to publish stream directly to CDN without passing through Zego real-time video cloud server. You can call this api to set params when pushing another streams
///
/// @param enable Whether to enable direct push CDN, YES: enable direct push CDN, NO: disable direct push CDN
/// @param config CDN configuration, if nil, use Zego's background default configuration
/// @param channel Publish stream channel
- (void)enablePublishDirectToCDN:(BOOL)enable config:(nullable ZegoCDNConfig *)config channel:(ZegoPublishChannel)channel;

/// set publish watermark
///
/// Set before publishing. The layout of the watermark cannot exceed the video encoding resolution of stream.
/// @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution. If it is nil, the watermark is cancelled.
/// @param isPreviewVisible the watermark is visible on local preview
- (void)setPublishWatermark:(nullable ZegoWatermark *)watermark isPreviewVisible:(BOOL)isPreviewVisible;

/// set publish watermark. You can call this api to set params when pushing another streams
///
/// Set before publishing. The layout of the watermark cannot exceed the video encoding resolution of stream.
/// @param watermark The upper left corner of the watermark layout is the origin of the coordinate system, and the area cannot exceed the size set by the encoding resolution. If it is nil, the watermark is cancelled.
/// @param isPreviewVisible the watermark is visible on local preview
/// @param channel Publish stream channel
- (void)setPublishWatermark:(nullable ZegoWatermark *)watermark isPreviewVisible:(BOOL)isPreviewVisible channel:(ZegoPublishChannel)channel;

/// Send SEI
///
/// This interface can synchronize some other additional information while the developer pushes streaming audio and video streaming data while sending streaming media enhancement supplementary information.
/// Generally, for scenarios such as synchronizing music lyrics or precise layout of video canvas, you can choose to use this api.
/// After the anchor sends the SEI, the audience can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
/// Since SEI information follows video frames or audio frames, and because of network problems, frames may be dropped, so SEI information may also be dropped. To solve this situation, it should be sent several times within the limited frequency.
/// Limit frequency: Do not exceed 30 times per second.
/// Note: This api is effective only when there is video data pushed. SEI information will not be sent without pushing video data.
/// The SEI data length is limited to 4096 bytes.
/// @param data SEI data
- (void)sendSEI:(NSData *)data;

/// Send SEI. You can call this api to set params when pushing another streams
///
/// This interface can synchronize some other additional information while the developer pushes streaming audio and video streaming data while sending streaming media enhancement supplementary information.
/// Generally, for scenarios such as synchronizing music lyrics or precise layout of video canvas, you can choose to use this api.
/// After the anchor sends the SEI, the audience can obtain the SEI content by monitoring the callback of [onPlayerRecvSEI].
/// Since SEI information follows video frames or audio frames, and because of network problems, frames may be dropped, so SEI information may also be dropped. To solve this situation, it should be sent several times within the limited frequency.
/// Limit frequency: Do not exceed 30 times per second.
/// Note: This api is effective only when there is video data pushed. SEI information will not be sent without pushing video data.
/// The SEI data length is limited to 4096 bytes.
/// @param data SEI data
/// @param channel Publish stream channel
- (void)sendSEI:(NSData *)data channel:(ZegoPublishChannel)channel;

/// On/off hardware encoding
///
/// Whether to use the hardware encoding function when publishing the stream, the GPU is used to encode the stream and to reduce the CPU usage. The setting can take effect before the stream published. If it is set after the stream published, the stream should be stopped first before it takes effect.
/// Because hard-coded support is not particularly good for a few models, ZegoExpressEngine uses software encoding by default. If the developer finds that the device is hot when pushing a high-resolution audio and video stream during testing of some models, you can consider calling this interface to enable hard coding.
/// @param enable Whether to enable hardware encoding, YES: enable hardware encoding, NO: disable hardware encoding
- (void)enableHardwareEncoder:(BOOL)enable;

/// set capture pipline scale mode. Whether the video data is scaled immediately when it is acquired or scaled when it is encoded.
///
/// This interface needs to be set before previewing or streaming.
/// The main effect is whether the local preview is affected when the acquisition resolution is different from the encoding resolution.
/// @param mode capture scale mode
- (void)setCapturePipelineScaleMode:(ZegoCapturePipelineScaleMode)mode;

@end

NS_ASSUME_NONNULL_END
