//
//  ZegoExpressEngine+Player.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Player)

/// Start playing stream
///
/// This interface allows users to play audio and video streams from the ZEGO audio and video cloud.
/// Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
/// In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
/// Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully pushed, the audio and video stream can be actually played.
/// The developer can update the player canvas by calling this interface again (the streamID must be the same).
/// @param streamID Stream ID, a string of up to 256 characters.
/// @param canvas The view used to display the pull flow picture. If the view is set to [nil], it will not be displayed.
- (void)startPlayingStream:(NSString *)streamID canvas:(nullable ZegoCanvas *)canvas;

/// Start playing stream
///
/// This interface allows users to play audio and video streams both from the ZEGO real-time audio and video cloud and from third-party cdn.
/// Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the [onRoomStreamUpdate] event callback.
/// In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the [onPlayerStateUpdate] event.
/// Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully pushed, the audio and video stream can be actually played.
/// The developer can update the player canvas by calling this interface again (the streamID must be the same).
/// @param streamID Stream ID
/// @param canvas The view used to display the pull flow picture. If the view is set to [nil], it will not be displayed.
/// @param config Advanced player configuration
- (void)startPlayingStream:(NSString *)streamID canvas:(nullable ZegoCanvas *)canvas config:(ZegoPlayerConfig *)config;

/// Stop playing stream
///
/// This interface allows the user to stop playing the stream. When stopped, the attributes set for this stream previously, such as [setPlayVolume], [mutePlayStreamAudio], [mutePlayStreamVideo], etc., will be invalid and need to be reset when playing the the stream next time.
/// @param streamID Stream ID, a string of up to 256 characters.
- (void)stopPlayingStream:(NSString *)streamID;

/// Set the playback volume of the stream
///
/// This interface is used to set the playback volume of the stream. Need to be called after calling startPlayingStream.
/// You need to reset after [stopPlayingStream] and [startPlayingStream].
/// @param volume Volume percentage. The value ranges from 0 to 100, and the default value is 100.
/// @param streamID Stream ID, a string of up to 256 characters.
- (void)setPlayVolume:(int)volume streamID:(NSString *)streamID;

/// Stop/resume pulling the audio data of the stream
///
/// This api can be used to stop pulling/retrieving the audio data of the stream. Need to be called after calling startPlayingStream.
/// This api is only effective for playing stream from ZEGO real-time audio and video cloud (not ZEGO CDN or third-party CDN).
/// @param mute mute flag, ture: mute play stream video, NO: resume play stream video
/// @param streamID Stream ID, a string of up to 256 characters.
- (void)mutePlayStreamAudio:(BOOL)mute streamID:(NSString *)streamID;

/// Stop/resume pulling the video data of the stream
///
/// This interface can be used to stop pulling/retrieving the video data of the stream. Need to be called after calling startPlayingStream.
/// This api is only effective for playing stream from ZEGO real-time audio and video cloud (not ZEGO CDN or third-party CDN).
/// @param mute mute flag, ture: mute play stream video, NO: resume play stream video
/// @param streamID Stream ID, a string of up to 256 characters.
- (void)mutePlayStreamVideo:(BOOL)mute streamID:(NSString *)streamID;

/// On/off hardware decoding
///
/// Turn on hardware decoding and use hardware to improve decoding efficiency. Need to be called before calling startPlayingStream.
/// Because hard-decoded support is not particularly good for a few models, ZegoExpressEngine uses software decoding by default. If the developer finds that the device is hot when playing a high-resolution audio and video stream during testing of some models, you can consider calling this interface to enable hard decoding.
/// @param enable Whether to turn on hardware decoding switch, YES: enable hardware decoding, NO: disable hardware decoding. The default is NO
- (void)enableHardwareDecoder:(BOOL)enable;

/// On/off frame order detection
///
/// @param enable Whether to turn on frame order detection, YES: enable check poc,not support B frames, NO: disable check poc, support B frames but the screen may temporary splash. The default is YES
- (void)enableCheckPoc:(BOOL)enable;

@end

NS_ASSUME_NONNULL_END
