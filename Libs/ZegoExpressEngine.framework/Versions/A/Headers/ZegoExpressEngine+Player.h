//
//  ZegoExpressEngine+Player.h
//  ZegoExpressEngine
//
//  Copyright © 2019 Zego. All rights reserved.
//

#import "ZegoExpressEngine.h"

NS_ASSUME_NONNULL_BEGIN

@interface ZegoExpressEngine (Player)

/// Start playting stream
/// @discussion This interface allows users to play audio and video streams from the ZEGO real-time audio and video cloud.Before starting to play the stream, you need to join the room first, you can get the new streamID in the room by listening to the onRoomStreamUpdate event callback.In the case of poor network quality, user play may be interrupted, the SDK will try to reconnect, and the current play status and error information can be obtained by listening to the onPlayerStateUpdate event.Playing the stream ID that does not exist, the SDK continues to try to play after executing this interface. After the stream ID is successfully pushed, the audio and video stream can be actually played.The developer can update the player canvas by calling this interface again(the streamID must be the same).
/// @param streamID Stream ID
/// @param canvas The view used to display the pull flow picture. If the view is set to empty, it will not be displayed.
- (void)startPlayingStream:(NSString *)streamID canvas:(nullable ZegoCanvas *)canvas;

/// Stop playing stream
/// @discussion This interface allows the user to stop playing the stream. When stopped, the attributes set for this stream previously, such as setPlayVolume, mutePlayStreamAudio, mutePlayStreamVideo, etc., will be invalid and need to be reset when playing the the stream next time.
/// @param streamID Stream ID
- (void)stopPlayingStream:(NSString *)streamID;

/// Set the playback volume of the stream
/// @discussion This interface is used to set the playback volume of the stream. Need to be called after calling startPlayingStream.
/// @param volume Volume percentage
/// @param streamID Stream ID
- (void)setPlayVolume:(int)volume stream:(NSString *)streamID;

/// Stop/resume pulling the audio data of the stream
/// @discussion This interface can be used to stop pulling/retrieving the audio data of the stream. Need to be called after calling startPlayingStream.
/// @param mute YES: pull audio is disabled; NO: resume pull audio.
/// @param streamID Stream ID
- (void)mutePlayStreamAudio:(BOOL)mute stream:(NSString *)streamID;

/// Stop/resume pulling the video data of the stream
/// @discussion This interface can be used to stop pulling/retrieving the video data of the stream. Need to be called after calling startPlayingStream.
/// @param mute YES: pull video is disabled; NO: resume pull video.
/// @param streamID Stream ID
- (void)mutePlayStreamVideo:(BOOL)mute stream:(NSString *)streamID;

/// On/off hardware decoding
/// @discussion Turn on hardware decoding and use hardware to improve decoding efficiency. Need to be called before calling startPlayingStream.
/// @param enable YES : enable hardware decoding; NO : turn off hardware decoding
- (void)enableHardwareDecoder:(BOOL)enable;

/// On/off frame order detection
/// @param enable YES to detect the frame order, B frames are not supported; NO not to detect the frame order, B frames are supported, and transient screens may appear
- (void)enableCheckPoc:(BOOL)enable;

@end

NS_ASSUME_NONNULL_END
