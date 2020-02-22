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
/// @discussion When the APIs are not used correctly, the callback prompts for detailed error information, which is controlled by the setDebugVerbose:language:  interface.
/// @param errorCode Error code, please refer to the common error code document for details.
/// @param funcName Function name
/// @param info Detailed error information
- (void)onDebugError:(int)errorCode funcName:(NSString *)funcName info:(NSString *)info;

#pragma mark Room Callback

/// Room status change notification
/// @discussion This callback is triggered when the connection status of the room changes, and the reason for the change is notified.
/// @param state Changed room status
/// @param errorCode Error code, please refer to the common error code document for details.
/// @param roomID Room ID
- (void)onRoomStateUpdate:(ZegoRoomState)state errorCode:(int)errorCode room:(NSString *)roomID;

/// In-room user access notification
/// @discussion This callback will be triggered when a user enters/exits the room and informs the current list of users in the room; note that the callback is only triggered when the isUserStatusNotify parameter in the ZegoRoomConfig passed loginRoom function is YES.
/// @param updateType Update type (add/delete)
/// @param userList List of users in the current room
/// @param roomID Room ID
- (void)onRoomUserUpdate:(ZegoUpdateType)updateType userList:(NSArray<ZegoUser *> *)userList room:(NSString *)roomID;

/// In-room stream update notification
/// @discussion When the user logs in to the room for the first time, he will receive a list of all the stream ID in the room; the list of flows that will be triggered by this callback notification will be triggered when the stream is added/deleted in the room.
/// @param updateType Update type (add/delete)
/// @param streamList Updated stream list
/// @param roomID Room ID
- (void)onRoomStreamUpdate:(ZegoUpdateType)updateType streamList:(NSArray<ZegoStream *> *)streamList room:(NSString *)roomID;

/// Stream extra information update notification
/// @discussion When other users publishing the stream update the extra information of the stream in the room, the local end will receive the callback
/// @param streamList List of streams that the extra info was updated.
/// @param roomID Room ID
- (void)onRoomStreamExtraInfoUpdate:(NSArray<ZegoStream *> *)streamList room:(NSString *)roomID;

#pragma mark Publisher Callback

/// Publish stream state callback
/// @discussion After publishing the stream successfully, the notification of the publish stream state change can be obtained through the callback interface.
/// @param state Publish stream state
/// @param errorCode The error code corresponding to the publish stream state change. Please refer to the common error code documentation
/// @param streamID Stream ID
- (void)onPublisherStateUpdate:(ZegoPublisherState)state errorCode:(int)errorCode stream:(NSString *)streamID;

/// Publish stream quality callback
/// @discussion After the successful publish, the callback will be received every 3 seconds. Through the callback, the collection frame rate, bit rate, RTT, packet loss rate and other quality data of the pushed audio and video stream can be obtained, and the health of the push stream can be monitored in real time.
/// @param quality Published stream quality, including audio and video frame rate, bit rate, resolution, RTT, etc.
/// @param streamID Stream ID
- (void)onPublisherQualityUpdate:(ZegoPublishStreamQuality *)quality stream:(NSString *)streamID;

/// Publish the stream to collect the first frame callback
/// @discussion After the successful publish, the SDK will receive this callback when it captures the first frame of data, including the first frame notification of the audio/video received.
/// @param event The event triggered when capture the first frame of the stream published includes the audio capture first frame and the video capture first frame event.
- (void)onPublisherRecvFirstFrameEvent:(ZegoPublisherFirstFrameEvent)event;

/// Captured video size change callback
/// @discussion After the successful publish, the callback will be received if there is a change in the video capture resolution in the process of publishing the stream.
/// @param size Video capture resolution
- (void)onPublisherVideoSizeChanged:(CGSize)size;

/// Add/Remove CDN address status callback
/// @discussion After the ZEGO real-time audio and video cloud relays the audio and video streams to the CDN, this callback will be received if the CDN relay status changes, such as a stop or a retry.
/// @param infoList List of information that the current CDN is relaying
/// @param streamID Stream ID
- (void)onPublisherRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList stream:(NSString *)streamID;

#pragma mark Player Callback

/// Play stream state callback
/// @discussion After calling the startPlayingStream successfully, this callback will be triggered every time the play state chaged, the new state can be obtained through the callback interface.
/// @param state Current play state
/// @param errorCode Error code
/// @param streamID Stream ID
- (void)onPlayerStateUpdate:(ZegoPlayerState)state errorCode:(int)errorCode stream:(NSString *)streamID;

/// Play stream quality callback
/// @discussion After calling the startPlayingStream successfully, this callback will be triggered every 3 seconds. The collection frame rate, bit rate, RTT, packet loss rate and other quality data  can be obtained, such the health of the push stream can be monitored in real time.
/// @param quality Quality of the stream
/// @param streamID Stream ID
- (void)onPlayerQualityUpdate:(ZegoPlayStreamQuality *)quality stream:(NSString *)streamID;

/// Play media event callback
/// @discussion This callback is triggered when an event such as audio and video jamming and recovery occurs in the pull stream.
/// @param event play media event enumeration
/// @param streamID Stream ID
- (void)onPlayerMediaEvent:(ZegoPlayerMediaEvent)event stream:(NSString *)streamID;

///  First frame event callback
/// @discussion After calling the startPlayingStream successfully, the callback is triggered when the first frame of the audio or the first frame of the video is received, the first frame of the video are rendered.
/// @param event Specific first  events received while playing
/// @param streamID Stream ID
- (void)onPlayerRecvFirstFrameEvent:(ZegoPlayerFirstFrameEvent)event stream:(NSString *)streamID;

/// Pull stream resolution change callback
/// @discussion If there is a change in the video resolution of the playing stream, the callback will be triggerd, and the user can adjust the display for that stream dynamiclly.
/// @param size Video resolution
/// @param streamID Stream ID
- (void)onPlayerVideoSizeChanged:(CGSize)size stream:(NSString *)streamID;

/// Receive  SEI
/// @discussion If "-sendSEI:" was called on remote, this callback will be triggered.
/// @param data SEI data
/// @param streamID stream ID
- (void)onPlayerRecvSEI:(NSData *)data stream:(NSString *)streamID;

#pragma mark Mixer Callback

/// Mixed stream relay CDN status update notification
/// @param infoList List of information that the current CDN is being mixed
/// @param taskID Mix stream task ID
- (void)onMixerRelayCDNStateUpdate:(NSArray<ZegoStreamRelayCDNInfo *> *)infoList taskID:(NSString *)taskID;

#pragma mark Device Callback

#if TARGET_OS_OSX
/// Audio device status change
/// @discussion only for macOS; This callback is triggered when an audio device is added or removed from the system. By listening to this callback, users can update the sound collection or output using a specific device when necessary.
/// @param deviceInfo Audio device information
/// @param updateType Update type (add/delete)
/// @param deviceType Audio device type
- (void)onAudioDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType deviceType:(ZegoAudioDeviceType)deviceType;
#endif

#if TARGET_OS_OSX
/// Video device status change
/// @discussion only for macOS; This callback is triggered when a video device is added or removed from the system. By listening to this callback, users can update the video capture using a specific device when necessary.
/// @param deviceInfo Audio device information
/// @param updateType Update type (add/delete)
- (void)onVideoDeviceStateChanged:(ZegoDeviceInfo *)deviceInfo updateType:(ZegoUpdateType)updateType;
#endif

/// Captured sound level update callback
/// @param soundLevel Locally captured sound level value, ranging from 0.0 to 100.0
- (void)onCapturedSoundLevelUpdate:(NSNumber *)soundLevel;

/// Remote sound level update callback
/// @param soundLevels Remote sound level dictionary, key is the streamID, value is the sound level value of the corresponding streamID
- (void)onRemoteSoundLevelUpdate:(NSDictionary<NSString *, NSNumber *> *)soundLevels;

/// Captured audio spectrum update callback
/// @param audioSpectrum Locally captured audio spectrum value list. Spectrum value range is [0-2^30]
- (void)onCapturedAudioSpectrumUpdate:(NSArray<NSNumber *> *)audioSpectrum;

/// Remote audio spectrum update callback
/// @param audioSpectrums Remote audio spectrum hashmap, key is the streamID, value is the audio spectrum list of the corresponding streamID. Spectrum value range is [0-2^30]
- (void)onRemoteAudioSpectrumUpdate:(NSDictionary<NSString *, NSArray<NSNumber *> *> *)audioSpectrums;

/// Device exception notification
/// @discussion This callback is triggered when an exception occurs when reading or writing the device.
/// @param errorCode Error code
/// @param deviceName Device Name
- (void)onDeviceError:(int)errorCode deviceName:(NSString *)deviceName;

/// Remote camera device status notification
/// @discussion When the state of the remote camera device changes, such as switching the camera, by monitoring this callback, it is possible to obtain an event related to the far-end camera, which can be used to prompt the user that the video may be abnormal.
/// @param state Remote camara status
/// @param streamID Stream ID
- (void)onRemoteCameraStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)streamID;

/// onRemoteMicStateUpdate
/// @discussion When the state of the remote microphone device is changed, such as switching a microphone, etc., by listening to the callback, it is possible to obtain an event related to the remote microphone, which can be used to prompt the user that the audio may be abnormal.
/// @param state Remote microphone status
/// @param streamID Stream ID
- (void)onRemoteMicStateUpdate:(ZegoRemoteDeviceState)state stream:(NSString *)streamID;

#pragma mark IM Callback

/// Receive room broadcast message notification
/// @param messageInfoList List of messages received
/// @param roomID Room ID
- (void)onIMRecvBroadcastMessage:(NSArray<ZegoMessageInfo *> *)messageInfoList roomID:(NSString *)roomID;

/// Receive room custom command notification
/// @param command Command content received
/// @param fromUser Sender of the command
/// @param roomID Room ID
- (void)onIMRecvCustomCommand:(NSString *)command fromUser:(ZegoUser *)fromUser roomID:(NSString *)roomID;

@end


#pragma mark - Media Player

@protocol ZegoMediaPlayerEventHandler <NSObject>

@optional

/// Player playback state callback
/// @param mediaPlayer Callback player instance
/// @param state Player's current state
/// @param errorCode Error code
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer stateUpdate:(ZegoMediaPlayerState)state errorCode:(int)errorCode;

/// Player network status event callback
/// @param mediaPlayer Callback player instance
/// @param networkEvent Network state event
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer networkEvent:(ZegoMediaPlayerNetworkEvent)networkEvent;

/// Player playback progress callback
/// @param mediaPlayer Callback player instance
/// @param millisecond Progress in milliseconds
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer playingProgress:(unsigned long long)millisecond;

@end


@protocol ZegoMediaPlayerVideoHandler <NSObject>

@optional

/// Player video frame raw data callback
/// @param mediaPlayer Callback player instance
/// @param data Bare data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame parameters
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFrameRawData:(const unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param;

/// Player video frame CVPixelBuffer data callback
/// @param mediaPlayer Callback player instance
/// @param buffer Video frame data packaged as CVPixelBuffer
/// @param param Video frame parameters
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer videoFramePixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param;

@end


@protocol ZegoMediaPlayerAudioHandler <NSObject>

@optional

/// Player audio frame data callback
/// @param mediaPlayer Callback player instance
/// @param data Raw data of audio frames
/// @param dataLength Data length
/// @param param Audio frame parameters
- (void)mediaPlayer:(ZegoMediaPlayer *)mediaPlayer audioFrameData:(const unsigned char *)data dataLength:(unsigned int)dataLength param:(ZegoAudioFrameParam *)param;

@end


#pragma mark - Custom Video IO

@protocol ZegoCustomVideoCaptureHandler <NSObject>

@optional

/// SDK notifies that video frames will be collected, and the video frame data sent to the SDK is only valid after receiving this callback
- (void)onStart;

/// SDK notifies to stop capturing video frames
- (void)onStop;

@end


@protocol ZegoCustomVideoRenderHandler <NSObject>

@optional

/// Local preview video frame raw data callback
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame parameters
/// @param flipMode Video frame flip mode
- (void)onCapturedVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode;

/// Remote stream custom video render video frame raw data callback, different streams are distinguished by streamID
/// @param data Raw data of video frames (eg: RGBA only needs to consider data[0], I420 needs to consider data[0,1,2])
/// @param dataLength Data length (eg: RGBA only needs to consider dataLength[0], I420 needs to consider dataLength[0,1,2])
/// @param param Video frame parameters
/// @param streamID Remote stream ID
- (void)onRemoteVideoFrameRawData:(unsigned char * _Nonnull * _Nonnull)data dataLength:(unsigned int *)dataLength param:(ZegoVideoFrameParam *)param stream:(NSString *)streamID;

/// Local preview video frame CVPixelBuffer data callback
/// @param buffer Video frame data packaged as CVPixelBuffer
/// @param param Video frame parameters
/// @param flipMode Video frame flip mode
- (void)onCapturedVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param flipMode:(ZegoVideoFlipMode)flipMode;

/// Remote stream video frame CVPixelBuffer data callback, different streams are distinguished by streamID
/// @param buffer Video frame data packaged as CVPixelBuffer
/// @param param Video frame parameters
/// @param streamID Remote stream ID
- (void)onRemoteVideoFrameCVPixelBuffer:(CVPixelBufferRef)buffer param:(ZegoVideoFrameParam *)param stream:(NSString *)streamID;

@end

NS_ASSUME_NONNULL_END
